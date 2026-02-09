#pragma once
#include "IToaster.h"
#include "SDK.h"
#include "v1/ILogger.h"
#include "v1/IProcessEvent.h"
#include "v1/IResolver.h"
#include "v1/IPlugin.h"
#include "v1/PluginBase.h"
#include "v1/ModuleLoader.h"
#include "v1/TaskBuilder.h"
#include "v1/IRuntime.h"

class Toaster : public IToaster {
    AIM_INJECTABLE(Toaster)
    AIM_INJECT(ILogger, log)
    AIM_INJECT(IRuntime, runtime)
    AIM_INJECT(IProcessEvent, processEvent)
    AIM_INJECT(TaskBuilder, taskBuilder)

    Toaster() = default;

    void toast(const std::wstring& title, const std::wstring& body) override {
        printf("\nToaster::toast() is toasting!!\n\n");
        processEvent_->enableTask(
            TaskBuilder()
                .name("Toast")
                .functionName("Function Engine.HUD.PostRender")
                .phase(HookPhase::Post)
                .callback([runtime = runtime_, title, body](InvocationContext& ctx) mutable {
                    auto* mgr = runtime->getFirst<UNotificationManager_TA>();
                    auto* notificationClass = runtime->classOf<UGenericNotification_TA>();
                    UNotification_TA* ret = mgr->PopUpOnlyNotification(notificationClass);
                    ret->SetTitle(FString(title));
                    ret->SetBody(FString(body));
                })
                .once()
                .build());
    }
    void test() override {
        toast(L"Toast", L"Testing");
    }
};

class ToastPlugin : public PluginBase<ToastPlugin> {
    ~ToastPlugin() override = default;
    auto getName() const -> const char* override { return "Toaster"; }

    void startup() override {
        registerModule(ModuleDefinition<Toaster>()
            .withDependency(&Toaster::__inject_log, "[default]")
            .withDependency(&Toaster::__inject_runtime, "[default]")
            .withDependency(&Toaster::__inject_processEvent, "[default]")
            .asSingleton()
        );
        setPluginReady();
    }

    void shutdown() override {
        setPluginYeetable();
    }

    auto registerPublicInterfaces() const -> std::vector<PublicInterface> override {
        return {
            expose<IToaster>(resolve<Toaster>())
        };
    }
};