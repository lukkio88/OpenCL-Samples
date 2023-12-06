cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(VectorAdd)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
set(GitProjectDir ${CMAKE_SOURCE_DIR}/../../)
set(OpenCL_external ${GitProjectDir}OpenCL-SDK/external/)
set(OpenCL_INCLUDE_DIR ${OpenCL_external}OpenCL-CLHPP/include)

if(WIN32)
set(OpenCL_OtherInclude ${OpenCL_external}OpenCL-Headers/)
endif()

message(STATUS ${OpenCL_INCLUDE_DIR})
message(STATUS ${OpenCL_OtherInclude})

set(OpenCL_LIBRARY_DIR ${GitProjectDir}OpenCL-SDK/install/lib/OpenCL.lib)

add_library(opencl STATIC IMPORTED)
set_target_properties(opencl PROPERTIES IMPORTED_LOCATION ${OpenCL_LIBRARY_DIR})

set(SRC_FILES main.cpp)
add_executable(vector-add ${SRC_FILES})
target_include_directories(vector-add PUBLIC ${OpenCL_INCLUDE_DIR} ${OpenCL_OtherInclude})
target_link_libraries(vector-add opencl)