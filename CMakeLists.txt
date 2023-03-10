cmake_minimum_required(VERSION 3.13)
project(Clock)
set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES src/include/Clock.hpp src/Clock.cpp src/main.cpp)

add_executable(Clock ${SOURCE_FILES})