VCVARS := C:\\Program Files\\Microsoft Visual Studio\\2022\\Community\\VC\\Auxiliary\\Build\\vcvars64.bat
GENERATOR := Ninja

.PHONY: configure build install clean vcvars

define run_with_vcvars
	cmd /C "$(VCVARS)" & $(1)
endef

configure:
	$(call run_with_vcvars, cmake -S . -B build -G $(GENERATOR) -DCMAKE_BUILD_TYPE=RelWithDebInfo)

build: configure
	$(call run_with_vcvars, cmake --build build --config RelWithDebInfo)

install: configure build
	$(call run_with_vcvars, cmake --install build --config RelWithDebInfo)

clean:
	@rm -rf build