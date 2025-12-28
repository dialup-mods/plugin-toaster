#pragma once
#include "IModule.h"

#ifdef TOAST_BUILD
    #define TOAST_API __declspec(dllexport)
#else
    #define TOAST_API __declspec(dllimport)
#endif

class TOAST_API IToaster : public IModule {
    AIM_INJECTABLE(IToaster)

    virtual void toast() = 0;
};
//virtual void toast(const std::wstring& title, const std::wstring& content, const int duration = 5) = 0;