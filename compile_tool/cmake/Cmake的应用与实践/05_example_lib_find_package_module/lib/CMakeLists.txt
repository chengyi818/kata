cmake_minimum_required(VERSION 3.16.3)
PROJECT(test_lib)

add_compile_options(-g)

# 编译动态库
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
message("INFO: " ${PROJECT_NAME})

add_library(${PROJECT_NAME}_shared SHARED test.c)
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

# make install
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/output)
message("CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH})
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX})

install(FILES include/test.h DESTINATION include)
install(TARGETS ${PROJECT_NAME}_shared
        LIBRARY DESTINATION lib)
