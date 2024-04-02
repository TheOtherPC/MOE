//
// Created by gru on 1/1/24.
//

#include "Renderer.h"

#include "glm/gtx/string_cast.hpp"
namespace MOE {
    ModelStruct::ModelStruct(MOE::Model m, std::vector<std::function<glm::mat4(glm::mat4)>> f) : model(m), funcs(f) {}
    std::vector<ModelStruct> Renderer::modelstructs;
    GLFWwindow* Renderer::window;
    float Renderer::lastX, Renderer::lastY, Renderer::SCR_HEIGHT, Renderer::SCR_WIDTH;
    Camera Renderer::camera;
    float Renderer::deltaTime = 0.0f, Renderer::lastFrame = 0.0f;
//    Shader Renderer::shader;
    std::vector<std::pair<Model, std::vector<std::function<glm::mat4(glm::mat4)>>>> Renderer::models;
    void Renderer::Init() {
        std::cout<<"Hello Renderer" << std::endl;
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//        stbi_set_flip_vertically_on_load(true);
    }
    void Renderer::ShutDown() {
        std::cout<<"Goodbye Renderer" << std::endl;
        glfwTerminate();
    }
    GLFWwindow* Renderer::InitWindow(const char *name, unsigned int height, unsigned int width) {
        Renderer::window = glfwCreateWindow(width, height, name, NULL, NULL);
        Renderer::lastX = width/2.0f;
        Renderer::lastY = height/2.0f;
        Renderer::SCR_HEIGHT = height;
        Renderer::SCR_WIDTH = width;
        glfwMakeContextCurrent(Renderer::window);
        glfwSetFramebufferSizeCallback(Renderer::window, framebuffer_size_callback);
        if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
            std::cout << "Failed to initialize GLAD" << std::endl;
        }
        glEnable(GL_DEPTH_TEST);
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        return Renderer::window;
    }
    void Renderer::Run() {
//        std::cout << "Hello" << std::endl;
//        stbi_set_fli/**/p_vertically_on_load(true);
//        while(!glfwWindowShouldClose(window)) {
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//            for(auto metamodel : models) {
//                glm::mat4 modelmatrix = glm::mat4(1.0f);
//                Shader shader("/home/gru/Desktop/Dev/Capstone/MOE/cmake-build-release/MOE/src/shader.vert", "/home/gru/Desktop/Dev/Capstone/MOE/cmake-build-release/MOE/src/shader.frag");
//                shader.use();
//                glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.1f, 100.0f);
//                glm::mat4 view = camera.GetViewMatrix();
//                shader.set("projection", projection);
//                shader.set("view", view);
//                for(auto func : metamodel.second) {
//                   modelmatrix = func(modelmatrix);
//                }
//                shader.set("model", modelmatrix);
//                metamodel.first.draw(shader); //is a pointer so it doesn't work
//            }
        for(auto metamodel : modelstructs) {
            glm::mat4 modelmatrix = glm::mat4(1.0f);
            Shader shader("../MOE/src/shader.vert", "../MOE/src/shader.frag");

            shader.use();
            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), float(SCR_WIDTH)/float(SCR_HEIGHT), 0.1f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();
            shader.set("projection", projection);
            shader.set("view", view);
            for(auto func : metamodel.funcs) {
                modelmatrix = func(modelmatrix);
            }
            shader.set("model", modelmatrix);

            metamodel.model.draw(shader); //is a pointer so it doesn't work
        }
//            Input::ProcessInput(Renderer::window);
        glfwSwapBuffers(Renderer::window);
        glfwPollEvents();
//        }
    }
    void Renderer::Set(MOE::Renderer::sets set) {
        if(set == FRAMEBUFFER) {
            std::cout << "set framebuffer" << std::endl;
            glfwSetFramebufferSizeCallback(Renderer::window, framebuffer_size_callback);
        } else if(set == MOUSE) {
            glfwSetCursorPosCallback(Renderer::window, mouse_callback);
        } else if(set == SCROLL) {
            glfwSetScrollCallback(Renderer::window, scroll_callback);
        } else if (set == INPUT) {
            glfwSetInputMode(Renderer::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    void Renderer::SetModels(std::vector<std::pair<Model, std::vector<std::function<glm::mat4(glm::mat4)>>>> inputModels) {
        Renderer::models = inputModels;
        std::cout << inputModels.size();
        std::cout << inputModels[0].second.size();
    }

    void Renderer::SetModels(std::vector<ModelStruct> inputModels) {
        Renderer::modelstructs = inputModels;
        std::cout << inputModels.size();
    }
    void Renderer::CloseWindow() {
        glfwSetWindowShouldClose(Renderer::window, true);
    }
    void Renderer::framebuffer_size_callback(GLFWwindow *window, int width, int height) {
        if (window == nullptr)
            return;
        glViewport(0,0, width, height);
    }
    void Renderer::mouse_callback(GLFWwindow *window, double xpos, double ypos) {
        float xoffset = xpos - lastX;
        float yoffset = ypos - lastY;
        lastX = xpos;
        lastY = ypos;
        camera.ProcessMouseMovement(xoffset, yoffset);
    }
    void Renderer::scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
        camera.ProcessMouseScroll(yoffset);
    }

    bool Renderer::endRenderer() {
        return glfwWindowShouldClose(Renderer::window);
    }
}