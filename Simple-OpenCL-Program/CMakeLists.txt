cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
project(OpenCL-test)

find_package( OpenCL REQUIRED)

if ( NOT OpenCL_FOUND )
    message(STATUS "This project requires the OpenCL library, and will not be compiled.")
    return()
endif()

set(SRC_FILES host.cpp)

set( CL_FILES device.cl )
source_group( "CL Files" FILES ${CL_FILES} )

add_executable(test-opencl ${SRC_FILES} ${CL_FILES})
include_directories(test-opencl ${OpenCL_INCLUDE_DIR})
target_link_libraries(test-opencl ${OpenCL_LIBRARY})