cmake_minimum_required(VERSION 3.16.3)
PROJECT(simple_cmake_04)

add_compile_options(-g)

# 编译动态库
add_subdirectory(lib)

include_directories(include)
add_executable(${PROJECT_NAME} src/main.c)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)

target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}_shared)
