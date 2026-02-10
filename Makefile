VCVARS := C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat
DIALUP_ROOT       := $(LOCALAPPDATA)/DialUp
include $(DIALUP_ROOT)/build-tools/common.mk
include $(DIALUP_ROOT)/build-tools/shell.mk

.PHONY: configure build install clean all

configure: check-shell
	$(call run_with_vcvars, cmake -S . -B build -G $(GENERATOR) -DCMAKE_BUILD_TYPE=RelWithDebInfo)

build: check-shell
	$(call run_with_vcvars, cmake --build build --config RelWithDebInfo)

install: check-shell
	$(call run_with_vcvars, cmake --install build --config RelWithDebInfo)

clean:
	@rm -rf build

all: check-shell clean configure build install
