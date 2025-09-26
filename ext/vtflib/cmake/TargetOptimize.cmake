macro(target_optimize TARGET)
    # Set optimization flags (MSVC defaults are fine)
    if(NOT MSVC)
        if(CMAKE_BUILD_TYPE MATCHES "Debug")
            # Build with no optimizations (debug-friendly optimization level is anything but) and debug symbols
            if(UNIX OR MINGW)
                target_compile_options(${TARGET} PRIVATE -O0 -g)
            endif()
            if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
                target_compile_options(${TARGET} PRIVATE -fno-limit-debug-info)
            endif()

            # Add debug define
            target_compile_definitions(${TARGET} PRIVATE DEBUG)
        else()
            # Build with optimizations and don't omit stack pointer for debugging
            if(UNIX OR MINGW)
                target_compile_options(${TARGET} PRIVATE -O2 -fno-omit-frame-pointer)
            endif()
        endif()
    endif()
endmacro()
