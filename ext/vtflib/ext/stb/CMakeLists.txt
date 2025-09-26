cmake_minimum_required(VERSION 3.16)
project(vtflib_stb)
set(CMAKE_CXX_STANDARD 20)

# Create library
add_library(${PROJECT_NAME} INTERFACE
        "${CMAKE_CURRENT_SOURCE_DIR}/include/stb_image_resize.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/stb_image_resize2.h")

target_include_directories(${PROJECT_NAME} INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)
