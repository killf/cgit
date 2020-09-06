cmake_minimum_required(VERSION 3.14)
project(cgit CXX)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")

add_executable(cgit src/main.cpp src/cgit.cpp src/string.hpp)

message(STATUS ${CMAKE_INSTALL_BINDIR})

install(TARGETS cgit RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})