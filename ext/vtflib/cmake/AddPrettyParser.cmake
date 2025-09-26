# Add a new parser library
function(add_pretty_parser TARGET)
    cmake_parse_arguments(PARSE_ARGV 1 OPTIONS "C" "" "DEPS;DEPS_PUBLIC;DEPS_INTERFACE;PRECOMPILED_HEADERS;SOURCES")

    if(OPTIONS_C)
        add_library(vtflib_${TARGET}c SHARED ${${PROJECT_NAME}c_SOURCES} ${OPTIONS_PRECOMPILED_HEADERS} ${OPTIONS_SOURCES})
        add_library(vtflib::${TARGET}c ALIAS vtflib_${TARGET}c)
        set_target_properties(vtflib_${TARGET}c PROPERTIES PREFIX "")
        target_link_libraries(vtflib_${TARGET}c PRIVATE vtflib::${TARGET})
        target_include_directories(vtflib_${TARGET}c PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/lang/c/include")
        string(TOUPPER ${TARGET} TARGET_UPPER)
        set(TARGET "vtflib_${TARGET}c")
    else()
        add_library(vtflib_${TARGET} STATIC ${OPTIONS_PRECOMPILED_HEADERS} ${OPTIONS_SOURCES})
        add_library(vtflib::${TARGET} ALIAS vtflib_${TARGET})
        set(TARGET "vtflib_${TARGET}")
    endif()
    if(NOT ("PRECOMPILED_HEADERS" IN_LIST OPTIONS_UNPARSED_ARGUMENTS))
        target_precompile_headers(${TARGET} PUBLIC ${OPTIONS_HEADERS})
    endif()
    target_link_libraries(${TARGET} PRIVATE ${OPTIONS_DEPS})
    target_link_libraries(${TARGET} PUBLIC ${PROJECT_NAME} ${OPTIONS_DEPS_PUBLIC})
    target_link_libraries(${TARGET} INTERFACE ${OPTIONS_DEPS_INTERFACE})

    # Define DEBUG macro
    target_compile_definitions(${TARGET} PRIVATE "$<$<CONFIG:Debug>:DEBUG>")

    # MSVC on its bullshit again
    if(MSVC)
        target_compile_options(${TARGET} PRIVATE "/Zc:preprocessor")
    endif()

    target_optimize(${TARGET})
endfunction()
