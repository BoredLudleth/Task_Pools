cmake_minimum_required (VERSION 3.0)

project (task_pools)

set (CMAKE_CXX_STANDARD 20)

set (SOURCES src/main.cpp src/rand_values.cpp)
set (HEADERS include/pool_lib.hpp include/rand_values.hpp)

include_directories(include/)

add_executable (a.out src/main.cpp src/rand_values.cpp)
