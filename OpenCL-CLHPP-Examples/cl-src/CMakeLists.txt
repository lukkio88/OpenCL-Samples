cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(project-name cl-src)
project(${project-name})

set(SRC vadd.cl v2scalar.cl v2v.cl)
add_custom_target(${project-name} SOURCES ${SRC})