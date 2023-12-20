cmake_minimum_required(VERSION 3.16.3)
PROJECT(simple_cmake)

add_compile_options(-g)
include_directories(include)
add_executable(hello src/main.c lib/test.c)

# add_custom_target(print_config ALL
# COMMAND ${CMAKE_COMMAND} -E echo "Config is $<CONFIG>"
# VERBATIM)