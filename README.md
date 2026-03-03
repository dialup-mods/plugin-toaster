## Synopsis

```c++
class BreakfastChef : public PluginBase<BreakfastChef> {
    void startup() override {
        setPluginReady();
        auto toaster = resolve<IToaster>();
        toaster->toast(L"Welcome.", L"You've got mail!");
    }
}
```
