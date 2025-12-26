#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <cstdio>
#include <memory>

#include "AsyncGate.h"
#include "ILogger.h"
#include "IModule.h"
#include "IPlugin.h"
#include "PluginBase.h"

#include "IToaster.h"
#include "SDK.h"
#include "IProcessEvent.h"

class Toaster : public IToaster {
    AIM_INJECTABLE(Toaster)
    void toast(std::string title, std::string body) override {
        printf("Toaster toast called\n");
        printf("    %s - %s", title.c_str(), body.c_str());
    }
};

class Toast : public PluginBase<Toast> {
    AIM_INJECTABLE(ToastPlugin)

  public:
    ~Toast() override = default;
    [[nodiscard]] auto getName() const -> const char* override { return "Toaster"; }
    void startup() override {
        printf("Toaster startup called\n");
    };

    auto registerPublicInterfaces() const -> std::vector<PublicInterface> override {
        return {};
        //    expose<IToaster>(resolve<Toaster>() )
        //};
    }

    void shutdown() override {
        printf("Toaster shutdown called\n");
    }

    void test() {
        auto foo = resolve<IProcessEvent>();
    }

};

extern "C" __declspec(dllexport) void*
create() {
    printf("✅ load() called\n");
    return new Toast();
}

extern "C" __declspec(dllexport) void
destroy() {
    MessageBoxA(nullptr, "Plugin destroyed!", "Test Plugin", MB_OK | MB_ICONINFORMATION);
}