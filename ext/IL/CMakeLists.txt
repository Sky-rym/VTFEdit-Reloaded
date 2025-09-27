cmake_minimum_required(VERSION 3.16)
project(vtflib_IL)
set(CMAKE_CXX_STANDARD 20)
include_guard(GLOBAL)

set(DEVIL_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")

function(target_link_devil TARGET)
    if(WIN32)
        get_target_property(TARGET_MSVC_RUNTIME_LIBRARY ${TARGET} MSVC_RUNTIME_LIBRARY)
        target_link_libraries(${TARGET} PRIVATE
            "${DEVIL_DIR}/lib/win_x86_64/DevIL.lib"
            "${DEVIL_DIR}/bin/win_x86_64/DevIL.dll")
    else()
        message(FATAL_ERROR "Unable to link to DevIL library!")
    endif()
    target_include_directories(${TARGET} PRIVATE "${DEVIL_DIR}/include")
endfunction()

# Create library
add_library(${PROJECT_NAME} INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/config.h.win"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/DevIL.i"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/devil_cpp_wrapper.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/devil_internal_exports.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/il.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/il_wrap.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ilu.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ilu_region.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ilut.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/ilut_config.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/luadevil.c"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/stamp-h.in")

target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
