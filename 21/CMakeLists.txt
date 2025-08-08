cmake_minimum_required(VERSION 3.31.6)
set(CMAKE_CXX_STANDARD 20)
project("AOC04")
add_executable(${PROJECT_NAME} main.cpp
        Solution.h
        SolutionInit.cpp
        Solution1.cpp
        Solution2.cpp
        util.cpp
        util.h
)
