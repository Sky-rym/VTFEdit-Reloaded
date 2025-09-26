function(add_vtflib_library TARGET)
    cmake_parse_arguments(PARSE_ARGV 1 OPTIONS "C;CSHARP;PYTHON;TEST;BENCH" "" "")
    string(TOUPPER ${TARGET} TARGET_UPPER)
    if(VTFLIB_USE_${TARGET_UPPER})
        set(PROPAGATE_VARS "")

        # Add C++
        include("${CMAKE_CURRENT_SOURCE_DIR}/src/${TARGET}/_${TARGET}.cmake")

        return(PROPAGATE ${PROPAGATE_VARS})
    endif()
endfunction()
