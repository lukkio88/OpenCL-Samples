cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(BasicTemplate)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
if(UNIX)
    set(OpenCL_INCLUDE_DIR /usr/local/cuda-10.0/include/)
    set(OpenCL_LIBRARY_DIR /usr/local/cuda-10.0/lib64/libOpenCL.so)
endif()

add_library(opencl SHARED IMPORTED)
set_target_properties(opencl PROPERTIES IMPORTED_LOCATION ${OpenCL_LIBRARY_DIR})

set(SRC_FILES main.cpp)
add_executable(basic-template ${SRC_FILES})
target_include_directories(basic-template PUBLIC ${OpenCL_INCLUDE_DIR})
target_link_libraries(basic-template opencl)