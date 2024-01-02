cmake_minimum_required(VERSION 3.27)
project(MOEProj)

set(CMAKE_CXX_STANDARD 17)

add_library(MOE SHARED
        src/MOE.h
        src/MOE/Application.cpp
        src/MOE/Application.h
        src/MOE/Renderer/Renderer.cpp
        src/MOE/Renderer/Renderer.h
        src/MOE/EntryPoint.h
)
