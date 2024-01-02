cmake_minimum_required(VERSION 3.27)
project(MOELib)

set(CMAKE_CXX_STANDARD 17)

add_library(MOE SHARED
        MOE.h
        MOE/Application.cpp
        MOE/Application.h
        MOE/Renderer/Renderer.cpp
        MOE/Renderer/Renderer.h
        MOE/EntryPoint.h
)