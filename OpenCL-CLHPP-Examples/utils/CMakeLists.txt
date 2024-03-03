cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(project-name utils)
project(${project-name})

set(SRC utils.h utils.cpp)
add_library(${project-name} STATIC ${SRC})
target_include_directories(${project-name} PUBLIC ${OpenCL_INCLUDE_DIR} ${OpenCL_OtherInclude} ./)
target_link_libraries(${project-name} opencl)