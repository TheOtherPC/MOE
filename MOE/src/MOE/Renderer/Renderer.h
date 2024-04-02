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
#include <vector>
#include <functional>

#include "Camera.h"
#include "Shader.h"
#include "Model.h"
//#include "../Input.h"
//#include "../Entity.h"

namespace MOE {
    struct ModelStruct {
        Model model;
        std::vector<std::function<glm::mat4(glm::mat4)>> funcs;
        ModelStruct(Model, std::vector<std::function<glm::mat4(glm::mat4)>>);
    };
    class Renderer {
    public:
        enum sets {FRAMEBUFFER, MOUSE, SCROLL, INPUT};
        static void Init();
        static void ShutDown();
        static GLFWwindow* InitWindow(const char *name, unsigned int height = 600, unsigned int width = 800);
        static void CloseWindow();
        static void Run();
        static void Set(sets set);
        static void SetModels(std::vector<std::pair<Model, std::vector<std::function<glm::mat4(glm::mat4)>>>>);
        static void SetModels(std::vector<ModelStruct>);
        static Camera camera;
//        static Shader shader;
//        static Model model;
        static GLFWwindow* window;
        static float deltaTime;
        static float lastFrame;
        static bool endRenderer();
        static std::vector<ModelStruct> modelstructs;

    private:
        static float lastX, lastY, SCR_WIDTH, SCR_HEIGHT;
        static std::vector<std::pair<Model, std::vector<std::function<glm::mat4(glm::mat4)>>>> models;
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
        static void mouse_callback(GLFWwindow* window, double xpos, double ypos);
        static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//        static void processInput(GLFWwindow* window);
    };
}

#endif //MOE_RENDERER_H
