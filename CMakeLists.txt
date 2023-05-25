cmake_minimum_required(VERSION 3.14)
project(cgit CXX)

set(CMAKE_CXX_STANDARD 11)

if (WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "/MT ${CMAKE_CXX_FLAGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "/MTd ${CMAKE_CXX_FLAGS}")
elseif (APPLE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
else ()
    set(CMAKE_CXX_FLAGS "-static ${CMAKE_CXX_FLAGS}")
endif ()
add_executable(cgit src/main.cpp src/cgit.cpp src/string.hpp src/utils.hpp src/utils.cpp)

message(STATUS ${CMAKE_INSTALL_BINDIR})

install(TARGETS cgit RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})