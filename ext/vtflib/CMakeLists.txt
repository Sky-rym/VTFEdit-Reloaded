cmake_minimum_required(VERSION 3.26 FATAL_ERROR)


# Create project
project(vtflib
        DESCRIPTION "A Valve VTF and VMT image format programming library."
        HOMEPAGE_URL "github.com/misyltoad/VTFLib")
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED OFF)


# Add scripts
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(AddPrettyParser)
include(AddSourcePPLibrary)
include(FetchContent)
include(IncludeSubdirectory)
include(PrintOptions)
include(TargetOptimize)


# Options (update print_options at the bottom of this file when modifying)
option(VTFLIB_LIBS_START_ENABLED "Libraries will all build by default"                             ON)

option(VTFLIB_BUILD_WITH_THREADS    "Build with support for threading"               ON)
option(VTFLIB_BUILD_WIN7_COMPAT     "Build with Windows 7 compatibility"             ON)

option(VTFLIB_LINK_STATIC_MSVC_RUNTIME "Link to static MSVC runtime library" OFF)


# Option overrides

if(MSVC)
    # MSVC does not rely on tbb for std::execution policies, so we can force this on
    set(VTFLIB_BUILD_WITH_TBB ON CACHE INTERNAL "" FORCE)
endif()


# Versioning published builds
if(PROJECT_IS_TOP_LEVEL AND NOT VTFLIB_VERSION)
    set(VTFLIB_VERSION "0.0.1")
    message(AUTHOR_WARNING "VTFLIB_VERSION is not defined, do not release this build publicly! Defaulting it to ${VTFLIB_VERSION}...")
endif()


# Set defaults after project call
if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_POSITION_INDEPENDENT_CODE ON)
endif()

if(VTFLIB_USE_STATIC_MSVC_RUNTIME)
    set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()

if(CMAKE_HOST_SYSTEM_NAME STREQUAL "Windows")
    # -----------------------------------------------------------------------------------
    # Code build definitions and features
    # -----------------------------------------------------------------------------------
    add_compile_definitions(
        WIN32
        _WIN64
        _DEBUG
        _WINDOWS
        _USRDLL
        VTFLIB_EXPORTS
    )
endif()


# Include thirdparty libraries
include_subdirectory(ext)


# Shared code
include_subdirectory(src/vtflib)


# Add libraries
add_vtflib_library(vtflib                              ) # vtflib::vtflib


# Print options
print_options(OPTIONS
        BUILD_WITH_THREADS BUILD_WIN7_COMPAT
        LINK_STATIC_MSVC_RUNTIME)
