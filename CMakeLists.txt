cmake_minimum_required(VERSION 3.10)
project(HeightMapGenerator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library(HeightMapGenerator STATIC src/HeightMapGenerator.cpp src/HeightMapGenerator.h)
target_include_directories(HeightMapGenerator PUBLIC include)