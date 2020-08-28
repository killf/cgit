cmake_minimum_required(VERSION 3.17)
project(cgit C)

set(CMAKE_C_STANDARD 11)

add_executable(cgit src/main.c src/cgit.c)