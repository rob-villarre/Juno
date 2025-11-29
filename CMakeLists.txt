cmake_minimum_required(VERSION 4.0)
project(Juno)

set(CMAKE_CXX_STANDARD 20)

find_path(RAYLIB_CPP_INCLUDE_DIRS "raylib-cpp.hpp")

add_library(${PROJECT_NAME} STATIC Source/library.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_CPP_INCLUDE_DIRS})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/Include)
