#pragma once
#include "IToaster.h"
#include "SDK.h"
#include "v1/ILogger.h"
#include "v1/IObjectQuery.h"
#include "v1/IProcessEvent.h"
#include "v1/IResolver.h"
#include "v1/IPlugin.h"
#include "v1/PluginBase.h"
#include "v1/ModuleLoader.h"
#include "v1/TaskBuilder.h"
#include "Runtime.h"

class Toaster : public IToaster {
    AIM_INJECTABLE(Toaster)
    AIM_INJECT(ILogger, log)
    AIM_INJECT(IObjectQuery, objectQuery)
    AIM_INJECT(IProcessEvent, processEvent)
    AIM_INJECT(TaskBuilder, taskBuilder)

    Toaster() = default;

    void toast(const FString& title, const FString& body, const int duration = 5) override {
        printf("\n\n\n\n toasting! \n\n\n\n");
        processEvent_->enableTask(
            TaskBuilder()
                .name("Toast")
                .functionName("Function Engine.HUD.PostRender")
                .phase(HookPhase::Post)
                .callback([objQ = objectQuery_, title, body](InvocationContext& ctx) {
                    auto* mgr = objQ->getFirst<UNotificationManager_TA>();
                    auto* notificationClass = objQ->classOf<UGenericNotification_TA>();
                    UNotification_TA* ret = mgr->PopUpOnlyNotification(notificationClass);
                    ret->SetTitle(title);
                    ret->SetBody(body);
                })
                .once()
                .build());
    }
    void test() override {
        printf("\n\n\n\n testing testing! \n\n\n\n");
        printf("PE? %p\n", processEvent_.get());
        auto task = TaskBuilder()
                .name("Toast")
                .functionName("Function Engine.HUD.PostRender")
                .phase(HookPhase::Post)
                .callback([objQ = objectQuery_](InvocationContext& ctx) {
                    printf("\n\n\n INSIDE OF CALLBACK \n\n\n");
                    printf("\n%s\n", Runtime::uobject_utils::getFullName(Runtime::ufunction::find("Function Engine.HUD.PostRender")).c_str());
                    auto* mgr = objQ->getFirst<UNotificationManager_TA>();
                    printf("\n\n\n INSIDE OF CALLBACK \n\n\n");
                    printf("\n mgr: %s\n", Runtime::uobject_utils::getFullName(mgr).c_str());
                    auto* notificationClass = objQ->classOf<UGenericNotification_TA>();
                    UNotification_TA* ret = mgr->PopUpOnlyNotification(notificationClass);
                    ret->SetTitle(FString(L"hey"));
                    ret->SetBody(FString(L"there"));
                })
                .once()
                .build();
        printf("built task\n");
        printf("task: %s\n", task->describe().c_str());
        processEvent_->enableTask(task);
    };
};

class ToastPlugin : public PluginBase<ToastPlugin> {
    ~ToastPlugin() override = default;
    auto getName() const -> const char* override { return "Toaster"; }
    void startup() override {
        registerModule(ModuleDefinition<Toaster>()
            .withDependency(&Toaster::__inject_log, "[default]")
            .withDependency(&Toaster::__inject_objectQuery, "[default]")
            .withDependency(&Toaster::__inject_processEvent, "[default]")
            .asSingleton()
        );
        setPluginReady();
    }
    void shutdown() override {
        setPluginYeetable();
    }
    auto registerPublicInterfaces() const -> std::vector<PublicInterface> {
        return {
            expose<IToaster>(resolve<Toaster>())
        };
    }
};