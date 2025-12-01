cmake_minimum_required(VERSION 4.0)
project(Juno)

set(CMAKE_CXX_STANDARD 20)

find_package(raylib CONFIG REQUIRED)
find_path(RAYLIB_CPP_INCLUDE_DIRS "raylib-cpp.hpp" REQUIRED)

add_library(${PROJECT_NAME} STATIC
    Include/Application.h
    Source/Application.cpp
        Source/Layer.cpp
        Include/Layer.h
        Source/LayerStack.cpp
        Include/LayerStack.h
        Include/IEntity.h
        Include/Command.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_include_directories(${PROJECT_NAME} PUBLIC
    ${RAYLIB_CPP_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/Include
)
