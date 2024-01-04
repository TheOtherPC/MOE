cmake_minimum_required(VERSION 3.27)
project(MOE)

set(CMAKE_CXX_STANDARD 17)

add_library(${PROJECT_NAME} STATIC
        MOE.h
        MOE/Application.cpp
        MOE/Application.h
        MOE/Renderer/Renderer.cpp
        MOE/Renderer/Renderer.h
        MOE/EntryPoint.h
)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
target_link_libraries(${PROJECT_NAME} glad glfw)

#include_directories(../vendor)