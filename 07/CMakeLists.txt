cmake_minimum_required(VERSION 3.11.0)
set(CMAKE_CXX_STANDARD 20)
project("AOC04")
add_executable(${PROJECT_NAME} main.cpp)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/input.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
