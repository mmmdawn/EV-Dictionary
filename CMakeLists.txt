cmake_minimum_required(VERSION 3.0)
project(Dictionary)
set(CMAKE_C_STANDARD 99)
include_directories(${CMAKE_SOURCE_DIR})

add_subdirectory(mylib)
add_subdirectory(sample.code)
