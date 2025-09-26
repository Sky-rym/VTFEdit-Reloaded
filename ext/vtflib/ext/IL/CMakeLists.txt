include_guard(GLOBAL)

set(IL_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")

function(target_link_devil TARGET)
    if(WIN32)
        get_target_property(TARGET_MSVC_RUNTIME_LIBRARY ${TARGET} MSVC_RUNTIME_LIBRARY)
        target_link_libraries(${TARGET} PRIVATE
            "${IL_DIR}/lib/DevIL.lib")
    else()
        message(FATAL_ERROR "Unable to link to DevIL library!")
    endif()
    target_include_directories(${TARGET} PRIVATE "${IL_DIR}/include")
endfunction()
