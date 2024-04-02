cmake_minimum_required(VERSION 3.27)
project(SandBoxProj)

set(CMAKE_CXX_STANDARD 17)

add_executable(SandBox src/main.cpp)

include_directories(${CMAKE_SOURCE_DIR}/MOE/src)
include_directories(${CMAKE_SOURCE_DIR}/MOE/vendor)
target_link_libraries(SandBox PUBLIC MOE)

configure_file(src/models/backpack/ao.jpg ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/backpack/backpack.obj ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/backpack/backpack.mtl ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/backpack/diffuse.jpg ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/backpack/normal.png ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/backpack/roughness.jpg ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/backpack/source_attribution.txt ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/backpack/specular.jpg ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/shrek/Shrek.mtl ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/shrek/Shrek.obj ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(src/models/shrek/T_Shrek.png ${CMAKE_BINARY_DIR} COPYONLY)
