list(APPEND ${PROJECT_NAME}_HEADERS
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VTFLib.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/Error.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/FileReader.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/FileWriter.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/Float16.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/MemoryReader.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/MemoryWriter.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/Proc.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/ProcReader.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/ProcWriter.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/Reader.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/Readers.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/resource.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/stdafx.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VMTFile.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VMTGroupNode.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VMTIntegerNode.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VMTNode.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VMTNodes.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VMTSingleNode.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VMTValueNode.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VMTWrapper.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VTFDXTn.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VTFFile.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VTFFormat.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VTFLib.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VTFMathlib.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/VTFWrapper.h"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/Writer.h"
        #"${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib2/VTFLib.h"
        #"${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/Resource.rc"
        "${CMAKE_CURRENT_SOURCE_DIR}/include/vtflib/Writers.h")

add_library(${PROJECT_NAME} SHARED
        ${${PROJECT_NAME}_HEADERS}
        "${CMAKE_CURRENT_LIST_DIR}/Error.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/FileReader.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/FileWriter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Float16.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/MemoryReader.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/MemoryWriter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/Proc.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ProcReader.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/ProcWriter.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VMTFile.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VMTGroupNode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VMTIntegerNode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VMTNode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VMTSingleNode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VMTValueNode.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VMTWrapper.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VTFFile.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VTFLib.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VTFMathlib.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/VTFWrapper.cpp")

target_precompile_headers(${PROJECT_NAME} PUBLIC ${${PROJECT_NAME}_HEADERS})

#target_link_libraries(${PROJECT_NAME} PUBLIC bufferstream sourcepp_half)

target_link_libraries(${PROJECT_NAME} PUBLIC CMP_Compressonator vtflib_stb)
target_link_libraries(${PROJECT_NAME} PRIVATE CMP_Compressonator vtflib_stb)
target_link_libraries(${PROJECT_NAME} INTERFACE CMP_Compressonator vtflib_stb)

target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:Debug>:DEBUG>")

#MSVC on its bullshit again
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/Zc:preprocessor")
endif()

target_optimize(${PROJECT_NAME})

