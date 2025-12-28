#pragma once
#include <string>

#include "IModule.h"

class UNotificationManager_TA;

class DIALUP_API IToaster : IModule {
    AIM_INJECTABLE(IToaster)

    virtual void toast() = 0;
};
//virtual void toast(const std::wstring& title, const std::wstring& content, const int duration = 5) = 0;
