cmake_minimum_required(VERSION 3.16.3)
PROJECT(simple_cmake_05)

add_compile_options(-g)

# 1. 预先编译动态库
# add_subdirectory(lib)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(test_LIBRARY REQUIRED)

IF(test_FOUND)
    message("INFO: " ${test_INCLUDE_DIR})
    include_directories(${test_INCLUDE_DIR})
    add_executable(${PROJECT_NAME} src/main.c)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
    target_link_libraries(${PROJECT_NAME} ${test_LIBRARY})
ELSE(test_FOUND)
    # 报错退出，终止编译
    message(FATAL_ERROR "cannot build")
ENDIF(test_FOUND)
