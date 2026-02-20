# must be set this way for it to work on bash and win shells
LOCALAPPDATA := $(shell powershell -NoProfile -Command "[Environment]::GetFolderPath('LocalApplicationData')")
DIALUP_ROOT       := $(LOCALAPPDATA)/DialUp
include $(DIALUP_ROOT)/build-tools/common.mk

.PHONY: configure build install install-impl clean all

.DEFAULT_GOAL := all

all: check-shell clean configure build install-with-prompt

configure: check-shell
	@echo $(DIALUP_ROOT)
	$(call run_with_vcvars, cmake -S . -B build -G $(GENERATOR) -DCMAKE_BUILD_TYPE=RelWithDebInfo)

build: check-shell
	$(call run_with_vcvars, cmake --build build --config RelWithDebInfo)

install: check-shell install-with-prompt

install-impl: check-shell
	$(call run_with_vcvars, cmake --install build --config RelWithDebInfo)

clean: check-shell
	@rm -rf build
