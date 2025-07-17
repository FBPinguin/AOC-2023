cmake_minimum_required(VERSION 3.31)
project(08)

set(CMAKE_CXX_STANDARD 20)

add_executable(08 main.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})