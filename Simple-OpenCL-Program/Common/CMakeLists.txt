cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(Common)

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

set(SRC_FILES common.cpp)

message("This is the CMAKE_SOURCE_DIR")
message("${CMAKE_SOURCE_DIR}")

add_library(common STATIC ${SRC_FILES})
include_directories(common ${OpenCL_INCLUDE_DIR} ./)
target_link_libraries(common ${OpenCL_LIBRARY})
set_target_properties(common PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
