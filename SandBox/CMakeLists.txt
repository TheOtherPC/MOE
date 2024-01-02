cmake_minimum_required(VERSION 3.27)
project(SandBoxProj)

set(CMAKE_CXX_STANDARD 17)

add_executable(SandBox src/main.cpp)
include_directories(${CMAKE_SOURCE_DIR}/MOE/src)
target_link_libraries(SandBox PUBLIC MOE)
