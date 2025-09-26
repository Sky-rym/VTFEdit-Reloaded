include_guard(GLOBAL)

set(COMPRESSONATOR_DIR "${CMAKE_CURRENT_LIST_DIR}" CACHE INTERNAL "")

function(target_link_compressonator TARGET)
    if(WIN32)
        get_target_property(TARGET_MSVC_RUNTIME_LIBRARY ${TARGET} MSVC_RUNTIME_LIBRARY)
        target_link_libraries(${TARGET} PRIVATE
            "${COMPRESSONATOR_DIR}/lib/win_x86_64/Compressonator_MT$<$<CONFIG:Debug>:d>.lib")
    else()
        message(FATAL_ERROR "Unable to link to Compressonator library!")
    endif()
    target_include_directories(${TARGET} PRIVATE "${COMPRESSONATOR_DIR}/include")
endfunction()
