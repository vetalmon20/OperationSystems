cmake_minimum_required(VERSION 3.17)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)

include_directories(lib)

add_executable(Lab1 main.cpp lib/demofuncs Manager.cpp Manager.h Functions.cpp Functions.h)

