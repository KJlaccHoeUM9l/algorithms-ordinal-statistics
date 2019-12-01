cmake_minimum_required(VERSION 3.13)
project(ordinal_statistics)

set(CMAKE_CXX_STANDARD 17)

add_executable(ordinal_statistics src/main.cpp src/ordinal_statistics.h src/utils.h utils/tests.h)