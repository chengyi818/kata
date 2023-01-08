cmake_minimum_required(VERSION 3.16.3)
PROJECT(simple_cmake_04)

add_compile_options(-g)

# 编译动态库
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/../output)
message("INFO: " ${PROJECT_NAME})

add_library(${PROJECT_NAME}_shared SHARED test.c)
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
