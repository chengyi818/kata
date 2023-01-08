cmake_minimum_required(VERSION 3.16.3)
PROJECT(simple_cmake_05)

add_compile_options(-g)

# 1. 预先编译动态库
# add_subdirectory(lib)

set(CMAKE_PREFIX_PATH ${PROJECT_SOURCE_DIR}/lib/output/cmake)
find_package(test_lib_shared REQUIRED)

IF(test_lib_shared_FOUND)
    add_executable(${PROJECT_NAME} src/main.c)
    set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
    target_link_libraries(${PROJECT_NAME} test_lib_shared)
ELSE(test_lib_shared_FOUND)
    # 报错退出，终止编译
    message(FATAL_ERROR "cannot build")
ENDIF(test_lib_shared_FOUND)
