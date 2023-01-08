cmake_minimum_required(VERSION 3.16.3)
PROJECT(simple_cmake)

add_compile_options(-g)
include_directories(include)
add_executable(hello src/main.c lib/test.c)