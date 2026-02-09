#pragma once
#include <string>

#include "IModule.h"
class FString;

class IToaster : public IModule {
public:
    virtual ~IToaster() = default;

private:
    AIM_INJECTABLE(IToaster)

    virtual void toast(const std::wstring& title, const std::wstring& content) = 0;
    virtual void test() = 0;
};