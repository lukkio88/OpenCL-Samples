cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(OpenCL-test)

set(CMAKE_CXX_STANDARD 11)

add_subdirectory(./ParallelSum)
add_subdirectory(./VectorSumParallel)
