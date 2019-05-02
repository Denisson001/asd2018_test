cmake_minimum_required(VERSION 2.8)
set(PROJECT_NAME "tests")
project(${PROJECT_NAME})

set(SOURCE_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../..)
set(TESTS_FILES_PATH ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -O2 -Wall")

add_executable(${PROJECT_NAME}  ${TESTS_FILES_PATH}/tests/main.cpp
                                ${TESTS_FILES_PATH}/tests/binary_heap_tests.cpp
                                ${TESTS_FILES_PATH}/tests/binomial_heap_tests.cpp
				${TESTS_FILES_PATH}/tests/fibonacci_heap_tests.cpp)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)
if(NOT Boost_FOUND)
	message(SEND_ERROR "Failed to find boost library")
	return()
else()
	target_include_directories(${PROJECT_NAME} PUBLIC ${Boost_INCLUDE_DIRS})
	target_link_libraries(${PROJECT_NAME} ${Boost_LIBRARIES})
endif()

target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/Binary_heap")
target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/Binomial_heap")
target_include_directories(${PROJECT_NAME} PUBLIC "${SOURCE_FILES_PATH}/Fibonacci_heap")
