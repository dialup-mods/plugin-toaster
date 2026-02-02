#pragma once
#include "IToaster.h"
#include "SDK.h"
#include "v1/ILogger.h"
#include "v1/IObjectProvider.h"
#include "v1/IProcessEvent.h"
#include "v1/ITaskBuilder.h"
#include "v1/Resolver.h"
#include "v1/IPlugin.h"
#include "v1/PluginBase.h"

#ifdef TOAST_BUILD
    #define TOAST_API __declspec(dllexport)
#else
    #define TOAST_API __declspec(dllimport)
#endif

class TOAST_API Toaster : public IToaster {
    AIM_INJECTABLE(Toaster)
    AIM_INJECT(ILogger, log)
    AIM_INJECT(IObjectProvider, objectProvider)
    AIM_INJECT(IProcessEvent, processEvent)
    AIM_INJECT(ITaskBuilder, taskBuilder)

    void toast(const FString& title, const FString& body, const int duration = 5) override {
        try {
            processEvent_->registerTask(
                taskBuilder_
                    ->name("Toast")
                    .functionName("Function Engine.HUD.PostRender")
                    .phase(HookPhase::Post)
                    .callback([objP = objectProvider_, title, body](InvocationContext& ctx) {
                        auto* mgr = objP->findInstanceOf<UNotificationManager_TA>();
                        auto* notificationClass = objP->classOf<UGenericNotification_TA>();
                        UNotification_TA* ret = mgr->PopUpOnlyNotification(notificationClass);
                        ret->SetTitle(title);
                        ret->SetBody(body);
                    })
                    .once()
                    .build());

        } catch (...) {
        }
    };
};

class TOAST_API ToastPlugin : public PluginBase<ToastPlugin> {
    auto getName() const -> const char* override { return "Toaster"; }
    void startup() override {
        registerModule(ModuleDefinition<Toaster>()
            .withDependency(&Toaster::__inject_log, "[default]")
            .withDependency(&Toaster::__inject_objectProvider, "[default]")
            .withDependency(&Toaster::__inject_processEvent, "[default]")
            .withDependency(&Toaster::__inject_taskBuilder, "[default]")
            .asSingleton()
        );

        setPluginReady();
    }
    void shutdown() override {}

    auto registerPublicInterfaces() const -> std::vector<PublicInterface> override {
        return {
            expose<IToaster>(resolve<Toaster>() )
        };
    }
};