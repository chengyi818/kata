cmake_minimum_required(VERSION 3.16.3)
PROJECT(simple_cmake_02)

add_compile_options(-g)
include_directories(include)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
set(LIBRARY_OUTPUT_NAME ${PROJECT_NAME})
message("INFO: " ${PROJECT_NAME})

add_library(${PROJECT_NAME}_shared SHARED lib/test.c)
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

add_executable(${PROJECT_NAME} src/main.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_shared)
