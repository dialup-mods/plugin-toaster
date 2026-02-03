#pragma once
#include "IModule.h"
class FString;

class IToaster : public IModule {
public:
    virtual ~IToaster() = default;

private:
    AIM_INJECTABLE(IToaster)

    virtual void toast(const FString& title, const FString& content, int duration = 5) = 0;
    virtual void test() = 0;
};