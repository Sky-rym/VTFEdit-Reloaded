cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# set up project
project(vtfedit
        DESCRIPTION "A utility to create, edit, and display every type of VTF file ever made."
        VERSION 2.1.7
        HOMEPAGE_URL "https://github.com/Sky-rym/VTFEdit-Reloaded")
set(PROJECT_NAME_PRETTY "VTFEdit Reloaded")
set(PROJECT_ORGANIZATION_NAME "Sky-rym" CACHE STRING "" FORCE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)
set(CMAKE_DOTNET_TARGET_FRAMEWORK_VERSION "v4.7.2")
#set(COMMON_LANGUAGE_RUNTIME netcore)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std:c++20")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -clr")
#set(MSVC true)

# options
option(VTFEDIT_BUILD_GUI       "Build ${PROJECT_NAME_PRETTY} GUI"        ON)
# option(VTFEDIT_BUILD_INSTALLER "Build ${PROJECT_NAME_PRETTY} installer" OFF)

# add helpers
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake/helpers")
include(CS_All)

# initial VS integration
cs_setup_vs_defaults(STARTUP_PROJECT "${PROJECT_NAME}")

# set common compile options
option(VTFEDIT_USE_LTO "Compile ${PROJECT_NAME_PRETTY} with LTO/IPO" OFF)
cs_configure_defaults(VTFEDIT_USE_LTO)

# external libraries
cs_include_directory(ext)

#include(CSharpUtilities)

# vtfedit
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/src/common/Config.h.in" "${CMAKE_CURRENT_SOURCE_DIR}/src/common/Config.h")
add_executable(${PROJECT_NAME}
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cli/VTFCmd.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cli/vtfcmd.rc"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cli/resource.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/stdafx.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/common/Config.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cli/enumerations.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/cli/enumerations.h")
cs_configure_target(${PROJECT_NAME} LOGO MANIFEST)
target_link_libraries(${PROJECT_NAME} PRIVATE vtflib)
#target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# vtfedit_gui
if(VTFEDIT_BUILD_GUI)
    add_executable(${PROJECT_NAME}_gui WIN32 MACOSX_BUNDLE
            #"${CMAKE_CURRENT_SOURCE_DIR}/res/gui/res.qrc"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/About.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/About.h"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/About.resx"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/BatchConvert.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/BatchConvert.h"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/BatchConvert.resx"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/DirectoryItemInfoManager.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/resource.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/Utility.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VMTCreate.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VMTCreate.h"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VMTCreate.resx"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VMTFileUtility.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFEdit.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFEdit.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFEdit.rc"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFEdit.resx"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFFileUtility.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFOptions.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFOptions.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFResources.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFResources.h"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFResources.resx"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/WADConvert.cpp"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/gui/WADConvert.h"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/WADConvert.resx"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/common/stdafx.h"
            "${CMAKE_CURRENT_SOURCE_DIR}/src/common/Config.h")

            #csharp_set_designer_cs_properties(
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/About.resx"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/BatchConvert.resx"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VMTCreate.resx"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFEdit.resx"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/VTFResources.resx"
            #"${CMAKE_CURRENT_SOURCE_DIR}/src/gui/WADConvert.resx"
            #)
    cs_configure_target(${PROJECT_NAME}_gui LOGO MANIFEST)
    target_link_devil(${PROJECT_NAME}_gui)
    target_link_libraries(${PROJECT_NAME}_gui PRIVATE vtflib)
    #target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
endif()

# installer
#if(VTFEDIT_BUILD_INSTALLER)
#    cs_include_directory(install)
#endif()

# copy the license
configure_file("${CMAKE_CURRENT_SOURCE_DIR}/LICENSE" "${CMAKE_BINARY_DIR}/LICENSE" COPYONLY)

# VS setup
if(WIN32 AND VTFEDIT_BUILD_GUI)
    set_target_properties(
            ${PROJECT_NAME}_gui PROPERTIES
            VS_DEBUGGER_ENVIRONMENT "PATH=%PATH%"
            CMAKE_VS_WINDOWS_TARGET_PLATFORM_VERSION 10.0)
endif()
