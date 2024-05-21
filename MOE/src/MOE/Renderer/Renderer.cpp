//
// Created by gru on 1/1/24.
//

#include "Renderer.h"

#include "glm/gtx/string_cast.hpp"
namespace MOE {
    ModelStruct::ModelStruct(MOE::Model m, std::vector<std::function<glm::mat4(glm::mat4)>> f) : model(m), funcs(f) {}
    std::vector<ModelStruct> Renderer::modelstructs;
    std::vector<glm::vec3> Renderer::positions;
    GLFWwindow* Renderer::window;
    unsigned int Renderer::boxVAO, Renderer::boxVBO;
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
        int i = 0;
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
//            std::cout <<positions[i].x << positions[i].y << positions[i].z << std::endl;
//            modelmatrix = glm::translate(glm::mat4(1.0f), positions[i]);
            shader.set("model", modelmatrix);
            RenderBoxes(metamodel.model.boundingBox);

            metamodel.model.draw(shader); //is a pointer so it doesn't work
            i++;
        }
//            Input::ProcessInput(Renderer::window);
        glfwSwapBuffers(Renderer::window);
        glfwPollEvents();
//        }
    }
    void Renderer::initBox() {
        glGenVertexArrays(1, &boxVAO);
        glGenBuffers(1, &boxVBO);

        glBindVertexArray(boxVAO);
        glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
        glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, sizeof(glm::vec3), (void*)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);
    }
    void Renderer::RenderBoxes(std::pair<glm::vec3, glm::vec3> box) {
        std::vector<glm::vec3> boundingBoxVertices = {
                // Bottom lines
                box.first, glm::vec3(box.second.x, box.first.y, box.first.z),
                glm::vec3(box.second.x, box.first.y, box.first.z), glm::vec3(box.second.x, box.first.y, box.second.z),
                glm::vec3(box.second.x, box.first.y, box.second.z), glm::vec3(box.first.x, box.first.y, box.second.z),
                glm::vec3(box.first.x, box.first.y, box.second.z), box.first,

                // Top lines
                glm::vec3(box.first.x, box.second.y, box.first.z), glm::vec3(box.second.x, box.second.y, box.first.z),
                glm::vec3(box.second.x, box.second.y, box.first.z), glm::vec3(box.second.x, box.second.y, box.second.z),
                glm::vec3(box.second.x, box.second.y, box.second.z), glm::vec3(box.first.x, box.second.y, box.second.z),
                glm::vec3(box.first.x, box.second.y, box.second.z), glm::vec3(box.first.x, box.second.y, box.first.z),

                // Side lines
                box.first, glm::vec3(box.first.x, box.second.y, box.first.z),
                glm::vec3(box.second.x, box.first.y, box.first.z), glm::vec3(box.second.x, box.second.y, box.first.z),
                glm::vec3(box.second.x, box.first.y, box.second.z), glm::vec3(box.second.x, box.second.y, box.second.z),
                glm::vec3(box.first.x, box.first.y, box.second.z), glm::vec3(box.first.x, box.second.y, box.second.z),
        };

        glBindBuffer(GL_ARRAY_BUFFER, boxVBO);
        glBufferData(GL_ARRAY_BUFFER, boundingBoxVertices.size() * sizeof(glm::vec3), boundingBoxVertices.data(), GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glLineWidth(2.0f);
        glColor3f(1.0f, 0.0f, 0.0f);
        glBindVertexArray(boxVAO);
        glDrawArrays(GL_LINES, 0, 24);
        glGetError();
        glBindVertexArray(0);
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