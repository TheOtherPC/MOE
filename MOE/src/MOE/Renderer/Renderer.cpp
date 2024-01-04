//
// Created by gru on 1/1/24.
//

#include "Renderer.h"

//namespace MOE::Renderer {
//    Renderer::Renderer() {
//
//    }
//}
namespace MOE {
    GLFWwindow* Renderer::window;
    float Renderer::lastX, Renderer::lastY;
    void Renderer::Init() {
        std::cout<<"Hello Renderer" << std::endl;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    }
    void Renderer::ShutDown() {
        std::cout<<"Goodbye Renderer" << std::endl;
        glfwTerminate();
    }
    void Renderer::InitWindow(const char *name, unsigned int height, unsigned int width) {
        Renderer::window = glfwCreateWindow(width, height, name, NULL, NULL);
        Renderer::lastX = width/2.0f;
        Renderer::lastY = height/2.0f;
    }
    void Renderer::CloseWindow() {
        glfwSetWindowShouldClose(Renderer::window, true);
    }
    void Renderer::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        glViewport(0,0, width, height);
    }
    void Renderer::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
        float xoffset = xpos - lastX;
        float yoffset = ypos - lastY;
        lastX = xpos;
        lastY = ypos;
        //camera.ProcessMouseMovement(xoffset, yoffset);
    }
    void Renderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        //camera.ProcessMouseScroll(xoffset, yoffset);
    }
}