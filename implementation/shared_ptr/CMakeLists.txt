cmake_minimum_required(VERSION 3.14)
project(shared_ptr)

set(CMAKE_CXX_STANDARD 14)

aux_source_directory(. SRC_LIST)
include_directories(. )

add_executable(shared_ptr main.cpp shared_ptr.cpp shared_ptr.h)