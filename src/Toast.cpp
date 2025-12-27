#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <cstdio>
#include <memory>

#include "AsyncGate.h"
#include "ILogger.h"
#include "IModule.h"
#include "IPlugin.h"
#include "PluginBase.h"

#include "IToaster.h"
#include "SDK.h"
#include "IProcessEvent.h"
#include "ITaskBuilder.h"


class Toaster final : public IToaster {
    AIM_INJECTABLE(Toaster)
    AIM_INJECT(ILogger, log)
    AIM_INJECT(IProcessEvent, processEvent)

    void toast(const std::string title, const std::string body) override {
        printf("Toaster toast called\n");
        printf("    %s - %s", title.c_str(), body.c_str());
    }
};

class Toast : public PluginBase<Toast> {
    AIM_INJECTABLE(ToastPlugin)

  public:
    ~Toast() override = default;
    [[nodiscard]] auto getName() const -> const char* override { return "Toaster"; }

    void startup() override {
        printf("Toaster startup called\n");

        //registerInstance<IProcessEvent>(processEvent);
        //processEvent->registerTask(taskBuilder->create()->
        //    name("Toast")
        //    .functionName("Function Engine.Interaction.Tick")
        //    .phase(HookPhase::Post)
        //    .callback([this](InvocationContext& ctx) {
        //        printf("callback\n");
        //    })
        //    .build());

        const auto processEvent = getResolver()->resolve<IProcessEvent>();
        const auto taskBuilder = getResolver()->resolve<ITaskBuilder>();

        printf("builder ok\n");

        auto task = taskBuilder
            ->name("Toast")
            .functionName("Function Engine.Interaction.Tick")
            .phase(HookPhase::Post)
            .callback([](InvocationContext&) {
                printf("callback\n");
            })
            .build();

        printf("build ok: %p\n", task.get());

        processEvent->registerTask(task);
        printf("register ok\n");


        //registerModule(
        //ModuleDefinition<Toaster>()
        //.withFactory([processEvent, taskBuilder]() {
        //    auto t = std::make_shared<Toaster>();
        //    t->__inject_processEvent(processEvent);
        //    t->__inject_taskBuilder(taskBuilder);
        //    return t;
        //})
        //.asSingleton()
        //);

        setPluginReady();
    };

    auto registerPublicInterfaces() const -> std::vector<PublicInterface> override {
        return {
            expose<IToaster>(resolve<Toaster>() )
        };
    }

    void shutdown() override {
        printf("Toaster shutdown called\n");
    }

    void test() {
        auto foo = resolve<IProcessEvent>();
    }

};

extern "C" __declspec(dllexport) void*
create() {
    printf("✅ load() called\n");
    return new Toast();
}

extern "C" __declspec(dllexport) void
destroy() {
    MessageBoxA(nullptr, "Plugin destroyed!", "Test Plugin", MB_OK | MB_ICONINFORMATION);
}

//template<typename T, typename... Deps>
//void registerComposedSingleton(Deps&&... deps) {
//    registerModule(
//        ModuleDefinition<T>()
//            .withFactory([=] {
//                auto obj = std::make_shared<T>();
//                (obj->*deps)...; // conceptually — see below
//                return obj;
//            })
//            .asSingleton()
//    );
//}