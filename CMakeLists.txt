cmake_minimum_required(VERSION 4.0)

set(DIALUP_PATH "$ENV{LOCALAPPDATA}/DialUpFramework")
set(DIALUP_PLUGINS_PATH "${DIALUP_PATH}/plugin")

include("${DIALUP_PATH}/SupportedTerminal.cmake")
include("${DIALUP_PATH}/Toolchain.cmake")

project(Toast VERSION 1.0 LANGUAGES CXX)

set(DIALUP_PATH "$ENV{LOCALAPPDATA}/DialUpFramework")
set(CMAKE_PREFIX_PATH
		"${DIALUP_PATH}"
		"${DIALUP_PATH}/plugin/AIM"
		"${DIALUP_PATH}/sdk"
)

set(INSTALL_DIR "${DIALUP_PLUGINS_PATH}/${PROJECT_NAME}")
set(CMAKE_INSTALL_PREFIX"${INSTALL_DIR}" CACHE PATH "Default install path" FORCE)

option(DEPLOY_TO_DEV "Copy plugin and PDB to dev plugins folder after build" ON)

set(SOURCES
    ${CMAKE_SOURCE_DIR}/src/${PROJECT_NAME}.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
include("${DIALUP_PATH}/EnsureABI.cmake")

set(INCLUDES
	${CMAKE_SOURCE_DIR}/src
	${CMAKE_SOURCE_DIR}/include
)

target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${INCLUDES}
    PUBLIC
        $<INSTALL_INTERFACE:include>
)

find_package(DialUpFramework REQUIRED)
find_package(AIM REQUIRED)
find_package(RLSDK REQUIRED)

target_compile_definitions(${PROJECT_NAME} PRIVATE TOAST_BUILD)

target_link_libraries(${PROJECT_NAME} PRIVATE DialUpFramework::DialUpFramework)
target_link_libraries(${PROJECT_NAME} PRIVATE AIM::AIM)
target_link_libraries(${PROJECT_NAME} PRIVATE RLSDK::RLSDK)

#dialup_setup_plugin(${PROJECT_NAME}
#		SOURCES ${SOURCES}
#		INCLUDES ${INCLUDES}
#)