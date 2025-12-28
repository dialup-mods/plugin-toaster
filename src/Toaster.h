#pragma once
#include "IToaster.h"
#include "IObjectProvider.h"
#include "IProcessEvent.h"
#include "ITaskBuilder.h"
#include "SDK.h"

class Toaster : public IToaster {
    AIM_INJECTABLE(Toaster)
    AIM_INJECT(IObjectProvider, objectProvider)
    AIM_INJECT(IProcessEvent, processEvent)
    AIM_INJECT(ITaskBuilder, taskBuilder)

    // fixme crashes
    //void toast(const std::wstring& title, const std::wstring& content, const int duration = 5) override {
    void toast() override {
        auto cls = UNotificationManager_TA::StaticClass();
        printf("got class;");
        auto notificationManager = objectProvider_->getByClass(cls);
        printf("got notificationManager?");
        return;
        auto title = std::wstring(L"foo");
        auto content= std::wstring(L"bar");
        int duration = 10;
        if (notificationManager != nullptr) {
            showToast_SEH(reinterpret_cast<UNotificationManager_TA*>(notificationManager), title, content, duration);
        }
    }

private:
    void showToast_SEH(UNotificationManager_TA* mgr, const std::wstring& title, const std::wstring& content, const int duration) {
        __try {
            auto* toaster = mgr->PopUpOnlyNotification(UGenericNotification_TA::StaticClass());
            //toaster->SetTitle(FString::SafeFString(title));
            //toaster->SetBody(FString::SafeFString(content));
            toaster->PopUpDuration = static_cast<float>(duration);
        } __except (EXCEPTION_EXECUTE_HANDLER) {
#ifdef _DEBUG
            MessageBoxW(nullptr, L"Toast notification exploded 💣", L"SEH Exception", MB_OK | MB_ICONERROR);
#endif
        }
    }

};

