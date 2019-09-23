cmake_minimum_required(VERSION 3.0.0)

project(algorithms-tests VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set (CMAKE_CXX_STANDARD 17)

enable_testing()

find_package(GTest REQUIRED)

include(GoogleTest)

include_directories(${GTEST_INCLUDE_DIR} "${CMAKE_CURRENT_SOURCE_DIR}/..")

add_executable(algorithms-tests algorithms-tests.cpp)

target_link_libraries(algorithms-tests ${GTEST_LIBRARY} ${GTEST_MAIN_LIBRARY} -pthread)

add_test(algorithms-tests algorithms-tests)
