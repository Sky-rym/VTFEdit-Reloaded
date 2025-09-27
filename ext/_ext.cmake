# global overrides
set(BUILD_SHARED_LIBS OFF) # here because of efsw, the little scamp

# vtflib
set(VTFLIB_LIBS_START_ENABLED ON CACHE INTERNAL "" FORCE)
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/vtflib")

# DevIL
add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/IL")

if(MARETF_BUILD_GUI)
    # Copy these in
    message(STATUS "I'm useless.")
endif()
