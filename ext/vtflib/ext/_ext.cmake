# compressonator
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/compressonator")

# stb
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/stb")

# DevIL
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/IL")


# Threads
if(VTFLIB_BUILD_WITH_THREADS)
    set(CMAKE_THREAD_PREFER_PTHREAD ON)
    set(THREADS_PREFER_PTHREAD_FLAG ON)
    find_package(Threads)
    if(NOT Threads_FOUND)
        set(VTFLIB_BUILD_WITH_THREADS OFF CACHE INTERNAL "" FORCE)
    endif()
endif()

function(vtflib_add_threads TARGET)
    if(VTFLIB_BUILD_WITH_THREADS)
        target_compile_definitions(${TARGET} PUBLIC VTFLIB_BUILD_WITH_THREADS)
        target_link_libraries(${TARGET} PRIVATE Threads::Threads)
    endif()
endfunction()
