cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME "heaps")
project(${PROJECT_NAME})

set(SOURCE_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O2 -Wall -Wl,--stack,256000000")

add_executable(${PROJECT_NAME}  ${SOURCE_FILES_PATH}/main/main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/Binary_heap")
target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/Binomial_heap")
target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/Fibonacci_heap")
