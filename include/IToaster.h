#pragma once
#include "IPlugin.h"
class FString;

class IToaster : public IPlugin {
public:
    virtual ~IToaster() = default;

private:
    AIM_INJECTABLE(IToaster)

    virtual void toast(const FString& title, const FString& content, int duration = 5) = 0;
};