cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ContextAndCommandQueue)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 14)

if(UNIX)
    set(OpenCL_INCLUDE_DIR /usr/local/cuda-10.0/include/)
    set(OpenCL_LIBRARY_DIR /usr/local/cuda-10.0/lib64/libOpenCL.so)
	add_library(opencl SHARED IMPORTED)
else()
	set(OpenCL_INCLUDE_DIR 
		${CMAKE_CURRENT_SOURCE_DIR}/../../OpenCL-SDK/external/OpenCL-CLHPP/include/ 
		${CMAKE_CURRENT_SOURCE_DIR}/../../OpenCL-SDK/external/OpenCL-Headers)
	set(OpenCL_LIBRARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../OpenCL-SDK/install/lib/OpenCL.lib)
	add_library(opencl STATIC IMPORTED)
endif()

set_target_properties(opencl PROPERTIES IMPORTED_LOCATION ${OpenCL_LIBRARY_DIR})
add_definitions(
	-DCL_HPP_ENABLE_EXCEPTIONS
	-DCL_TARGET_OPENCL_VERSION=120
	-DCL_HPP_TARGET_OPENCL_VERSION=120
	-DCL_HPP_MINIMUM_OPENCL_VERSION=120)

set(SRC_FILES main.cpp)
add_executable(context-command-queue ${SRC_FILES})
target_include_directories(context-command-queue PUBLIC ${CMAKE_SOURCE_DIR} ${OpenCL_INCLUDE_DIR})
target_link_libraries(context-command-queue opencl)
