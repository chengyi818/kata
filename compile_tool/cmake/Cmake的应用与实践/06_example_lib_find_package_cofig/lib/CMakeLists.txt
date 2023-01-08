cmake_minimum_required(VERSION 3.16.3)
PROJECT(test_lib)

add_compile_options(-g)

# 编译动态库
# set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output)
message("INFO: " ${PROJECT_NAME})


add_library(${PROJECT_NAME}_shared SHARED test.c)
set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME}_shared PUBLIC
                        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
                        $<INSTALL_INTERFACE:include>)               
set_target_properties(${PROJECT_NAME}_shared PROPERTIES PUBLIC_HEADER "include/test.h")

# make install
set(CMAKE_INSTALL_PREFIX ${PROJECT_SOURCE_DIR}/output)
message("CMAKE_INSTALL_PREFIX: " ${CMAKE_INSTALL_PREFIX})

install(TARGETS ${PROJECT_NAME}_shared
        EXPORT ${PROJECT_NAME}_shared-targets
        PUBLIC_HEADER DESTINATION include
        LIBRARY DESTINATION lib)
install(EXPORT ${PROJECT_NAME}_shared-targets
        FILE ${PROJECT_NAME}_sharedConfig.cmake
        DESTINATION cmake)
