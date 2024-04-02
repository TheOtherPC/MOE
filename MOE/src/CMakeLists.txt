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
        MOE/Input.cpp
        MOE/Input.h
        MOE/Renderer/Shader.h
        MOE/Renderer/Shader.cpp
        MOE/Renderer/Mesh.cpp
        MOE/Renderer/Mesh.h
        MOE/Renderer/Model.cpp
        MOE/Renderer/Model.h
        MOE/Renderer/Camera.cpp
        MOE/Renderer/Camera.h
        MOE/Physics/Physics.cpp
        MOE/Physics/Physics.h
        MOE/Entity.cpp
        MOE/Entity.h
)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
#include_directories(../vendor/bullet3/src)
#INCLUDE_DIRECTORIES(
#        ${BULLET_PHYSICS_SOURCE_DIR}/src
#)
include_directories(${CMAKE_SOURCE_DIR}/vendor/bullet/src)
target_link_libraries(${PROJECT_NAME} glad glfw assimp BulletDynamics BulletCollision LinearMath)
configure_file(MOE/Renderer/shaders/shader.frag ${CMAKE_BINARY_DIR}/MOE/src COPYONLY)
configure_file(MOE/Renderer/shaders/shader.vert ${CMAKE_BINARY_DIR}/MOE/src COPYONLY)

#include_directories(../vendor)