#pragma once
#include <string>

#include "IModule.h"

struct IToaster : IModule {
    AIM_INJECTABLE(IToaster)

    virtual void toast(std::string title, std::string body) = 0;
};