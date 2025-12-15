cmake_minimum_required(VERSION 3.20)
project(cstandard)

set(CMAKE_CXX_STANDARD 23)

add_executable(cstandard main.cpp c++_23.cc)

#tbb
target_link_libraries(cstandard pthread rt)
