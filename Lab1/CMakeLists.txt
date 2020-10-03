cmake_minimum_required(VERSION 3.17)
project(Lab1)

set(CMAKE_CXX_STANDARD 20)

include_directories(Lib Utils)

add_executable(Lab1 main.cpp Lib/demofuncs Manager.cpp Manager.h Utils/Utils.cpp Utils/Utils.h)

