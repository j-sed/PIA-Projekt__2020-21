cmake_minimum_required(VERSION 3.17)
project(resic)

set(CMAKE_CXX_STANDARD 11)

add_executable(resic resic.cpp resic.h main.cpp sit.hpp)