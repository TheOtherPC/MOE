//
// Created by gru on 1/1/24.
//

#include "Application.h"

namespace MOE {
//    EntityStruct::EntityStruct(MOE::Model a, std::vector<std::function<glm::mat4(glm::mat4)>> b, float c) : model(a), transforms(b), mass(c) {
//
//    }
    Application::Application() {
        std::cout << "Hello Application" << std::endl;
        Renderer::Init();
        Physics::Init();
        Audio::Init();
    }
    Application::~Application() {
        Renderer::ShutDown();
        Physics::ShutDown();
        Audio::ShutDown();
        std::cout << "Goodbye Application" << std::endl;
    }

    void Application::Run() {
        std::cout << "Run Application" << std::endl;
//        Physics::SetWorld();
        while(!glfwWindowShouldClose(Renderer::window)){
            Input::ProcessInput(Renderer::window);
            Physics::Run();
            Entity::updatePositions();
            Renderer::positions = Physics::GetPositions();
//            Renderer::initBox();
//            std::cout << Renderer::positions[1].x << Renderer::positions[1].y << Renderer::positions[1].z;
            Renderer::Run();
        }
    }

}