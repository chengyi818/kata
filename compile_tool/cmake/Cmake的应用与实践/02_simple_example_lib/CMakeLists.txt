cmake_minimum_required(VERSION 3.16.3)
PROJECT(simple_cmake_02)

add_compile_options(-g)
include_directories(include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)

add_library(test_static STATIC lib/test.c)
add_library(test SHARED lib/test.c)
# 同时编译动态和静态库
set_target_properties(test_static PROPERTIES OUTPUT_NAME "test")

# target_link_libraries(test)
# add_executable(hello src/main.c)