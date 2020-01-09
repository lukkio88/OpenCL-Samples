cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(OpenCL-test)

set(CMAKE_CXX_STANDARD 11)
if(DEFINED ENV{OpenCL_INCLUDE_DIR})
    set(OpenCL_INCLUDE_DIR $ENV{OpenCL_INCLUDE_DIR})
else()
    message("Could not find environment variable OpenCL_INCLUDE_DIR")
endif()

if(DEFINED ENV{OpenCL_LIBRARY})
    set(OpenCL_LIBRARY $ENV{OpenCL_LIBRARY})
else()
    message("Could not find environment variable OpenCL_LIBRARY")
endif()

find_package(OpenCL REQUIRED)

if (NOT OpenCL_FOUND )
    message(STATUS "This project requires the OpenCL library, and will not be compiled.")
    return()
endif()

set(SRC_FILES host.cpp)

set(CL_FILES device.cl)
source_group("CL Files" FILES ${CL_FILES})

add_executable(test-opencl ${SRC_FILES} ${CL_FILES})
include_directories(test-opencl ${OpenCL_INCLUDE_DIR})
target_link_libraries(test-opencl ${OpenCL_LIBRARY})
