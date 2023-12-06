cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(opencl-cpp-examples)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 17)
add_compile_definitions(CL_KERNEL_PATH="${CMAKE_SOURCE_DIR}/cl-src")
set(GitProjectDir ${CMAKE_SOURCE_DIR}/../)
set(OpenCL_external ${GitProjectDir}OpenCL-SDK/external/)
set(OpenCL_INCLUDE_DIR ${OpenCL_external}OpenCL-CLHPP/include)

if(WIN32)
set(OpenCL_OtherInclude ${OpenCL_external}OpenCL-Headers/)
endif()

set(EXAMPLES-OPENCL-CPP 
	cl-src
	print-platforms-and-devices 
	vector-add
	vec2vec
	vec2scalar)

set(OpenCL_LIBRARY_DIR ${GitProjectDir}OpenCL-SDK/install/lib/OpenCL.lib)

if(NOT TARGET opencl)
	add_library(opencl STATIC IMPORTED)
	set_target_properties(opencl PROPERTIES IMPORTED_LOCATION ${OpenCL_LIBRARY_DIR})
endif()

function(BUILD_TARGET project-name)
	set(SRC_FILES main.cpp)
	add_executable(${project-name} ${SRC_FILES})
	target_include_directories(${project-name} PUBLIC ${OpenCL_INCLUDE_DIR} ${OpenCL_OtherInclude})
	target_link_libraries(${project-name} opencl)
endfunction()

foreach(EXAMPLE ${EXAMPLES-OPENCL-CPP})
	add_subdirectory(./${EXAMPLE})
endforeach()