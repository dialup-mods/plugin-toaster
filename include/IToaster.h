#pragma once
#include "v1/IModule.h"
class FString;

class IToaster : public IModule {
public:
    virtual ~IToaster() = default;

private:
    AIM_INJECTABLE(IToaster)

    virtual void toast(const FString& title, const FString& content, int duration = 5) = 0;
};