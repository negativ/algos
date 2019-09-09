cmake_minimum_required(VERSION 3.0.0)

project(algorithms VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set (CMAKE_CXX_STANDARD 17)

find_package(Qt5Core)

include_directories(${CMAKE_INCLUDE_CURRENT_DIR})

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} Qt5::Core)
