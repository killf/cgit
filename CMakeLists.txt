cmake_minimum_required(VERSION 3.17)
project(cgit CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(cgit src/main.cpp src/cgit.cpp src/string.hpp)