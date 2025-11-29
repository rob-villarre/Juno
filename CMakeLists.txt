cmake_minimum_required(VERSION 4.0)
project(Juno)

set(CMAKE_CXX_STANDARD 20)

add_library(${PROJECT_NAME} STATIC Source/library.cpp)

