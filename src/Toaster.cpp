#include <cstdio>
#include "Toaster.h"

extern "C" __declspec(dllexport) void*
create() {
    printf("load() called\n");
    return new Toaster();
}

extern "C" __declspec(dllexport) void
destroy() {}
