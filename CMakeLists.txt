cmake_minimum_required(VERSION 3.14)
project(cgit CXX)

set(CMAKE_CXX_STANDARD 11)

IF (WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT ${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd ${CMAKE_CXX_FLAGS}")
ELSE ()
set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")
ENDIF ()
add_executable(cgit src/main.cpp src/cgit.cpp src/string.hpp)

message(STATUS ${CMAKE_INSTALL_BINDIR})

install(TARGETS cgit RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})