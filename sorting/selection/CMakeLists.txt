cmake_minimum_required(VERSION 3.15)
project(selection)

set(CMAKE_CXX_STANDARD 14)

add_executable(selection main.cpp RANDOM_GENERATOR.cpp RANDOM_GENERATOR.h SORTER.cpp SORTER.h MEASUREMENT.cpp MEASUREMENT.h)