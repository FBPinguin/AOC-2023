cmake_minimum_required(VERSION 3.31)
project(16)

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} main.cpp
        Solution.h
        SolutionInit.cpp
        Solution1.cpp
        Solution2.cpp
        util.cpp
        util.h
)
