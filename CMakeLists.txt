cmake_minimum_required (VERSION 3.0)

project (task_pools)

set (CMAKE_CXX_STANDARD 20)

set (SOURCES src/main.cpp)
set (HEADERS include/pool_lib.hpp)

include_directories(include/)

add_executable (a.out src/main.cpp)
