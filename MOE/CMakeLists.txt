cmake_minimum_required(VERSION 3.27)
project(MOE)

set(CMAKE_CXX_STANDARD 17)


include_directories(vendor)

add_subdirectory(vendor/glfw)
add_subdirectory(vendor/glad)
add_subdirectory(vendor/assimp)
add_subdirectory(vendor/bullet3)
add_subdirectory(src)