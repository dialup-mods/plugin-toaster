cmake_minimum_required(VERSION 4.0)

project(Toast VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_SYSTEM_PROCESSOR x86_64)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_COMPILER "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64/cl.exe" CACHE FILEPATH "C Compiler" FORCE)
set(CMAKE_CXX_COMPILER "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64/cl.exe" CACHE FILEPATH "C++ Compiler" FORCE)
set(CMAKE_LINKER "C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.44.35207/bin/Hostx64/x64/link.exe" CACHE FILEPATH "Linker" FORCE)

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_BUILD_TYPE "RelWithDebInfo" CACHE STRING "" FORCE)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")  # `/MD`
set(CMAKE_GENERATOR_TOOLSET "v142" CACHE STRING "Toolset version")

set(compile_options
		/std:c++20
		/bigobj
		/EHsc
		/MP
		/utf-8
		/Zi # generate debug info
)

set(CMAKE_PREFIX_PATH
		"$ENV{LOCALAPPDATA}/DialUpFramework"
		"$ENV{LOCALAPPDATA}/DialUpFramework/sdk"
)
find_package(DialUpFramework REQUIRED)

option(DEPLOY_TO_DEV "Copy plugin and PDB to dev plugins folder after build" ON)

find_package(RLSDK REQUIRED)

get_target_property(lib RLSDK::RLSDK IMPORTED_IMPLIB_RELWITHDEBINFO)
if(lib)
	set_target_properties(RLSDK::RLSDK PROPERTIES IMPORTED_IMPLIB "${lib}")
endif()

get_target_property(lib DialUpFramework::DialUpFramework IMPORTED_IMPLIB_RELWITHDEBINFO)
if(lib)
	set_target_properties(DialUpFramework::DialUpFramework PROPERTIES IMPORTED_IMPLIB "${lib}")
endif()

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME}.cpp
)

set(INCLUDES
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/include
    $ENV{LOCALAPPDATA}/DialUpFramework/include
	$ENV{LOCALAPPDATA}/DialUpFramework/plugin/AIM/include
)

dialup_setup_plugin(${PROJECT_NAME}
		SOURCES ${SOURCES}
		INCLUDES ${INCLUDES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE RLSDK::RLSDK)
target_link_libraries(${PROJECT_NAME} PRIVATE DialUpFramework::DialUpFramework)
