cmake_minimum_required(VERSION 3.27)
project(MOEProj)

set(CMAKE_CXX_STANDARD 17)


include_directories(vendor)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(src)