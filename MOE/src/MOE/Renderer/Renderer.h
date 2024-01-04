//
// Created by gru on 1/1/24.
//
#ifndef MOE_RENDERER_H
#define MOE_RENDERER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

namespace MOE {
    class Renderer {
    public:
        static void Init();
        static void ShutDown();
        static void InitWindow(const char *name, unsigned int height = 600, unsigned int width = 800);
        static void CloseWindow();
    private:
        static float lastX, lastY;
        static GLFWwindow* window;
        void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
        void processInput(GLFWwindow* window);
    };
}

#endif //MOE_RENDERER_H
