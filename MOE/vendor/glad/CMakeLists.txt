cmake_minimum_required (VERSION 3.27)
project(Glad)

add_library(glad include/glad/glad.h src/glad.c
        ../stb/stb_image.cpp)
target_include_directories(glad PUBLIC include/)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
