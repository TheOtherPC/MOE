#include <iostream>
#include "MOE.h"


class SandBox : public MOE::Application {
public:
    SandBox() {
        MOE::Renderer::InitWindow("Thing");
        MOE::Renderer::Set(MOE::Renderer::FRAMEBUFFER);
        MOE::Renderer::Set(MOE::Renderer::MOUSE);
        MOE::Renderer::Set(MOE::Renderer::SCROLL);
//        MOE::Renderer::Set(MOE::Renderer::INPUT);
        Run();

    }
    void Run() {
//        MOE::Model backpack ("models/backpack/backpack.obj");
        MOE::Model backpack ("/home/gru/Desktop/Dev/Capstone/MOE/SandBox/src/models/backpack/backpack.obj", true);
        MOE::Model shrek ("/home/gru/Desktop/Dev/Capstone/MOE/SandBox/src/models/shrek/Shrek.obj", false);
        std::vector<std::pair<MOE::Model, std::vector<std::function<glm::mat4(glm::mat4)>>>> models;
        std::vector<MOE::ModelStruct> thing;
        std::vector<MOE::EntityStruct> entities;
        std::vector<std::function<glm::mat4(glm::mat4)>> transforms;
        transforms.emplace_back([](glm::mat4 m){return glm::translate(m, glm::vec3(0.0f, 0.0f, -0.5f));});
        transforms.emplace_back([](glm::mat4 m){return glm::scale(m, glm::vec3(0.1f, 0.1f, 0.1f));});
        transforms.emplace_back([](glm::mat4 m){return glm::rotate(m, glm::radians(float(glfwGetTime()) * 25.0f), glm::vec3(0.0f, 1.0f, 0.0f));});
        //For input, have data structure similar to transforms, but instead of functions for transformations it is functions for keyboard controls.
        //The Pair would be the keycode and then the function.
//        models.emplace_back(backpack, transforms);
        thing.emplace_back(backpack, transforms);
        entities.emplace_back(backpack, transforms, 1.0f);
        std::vector<std::function<glm::mat4(glm::mat4)>> transforms1;
        transforms1.emplace_back([](glm::mat4 m){return glm::translate(m, glm::vec3(0.5f, 0.0f, -0.5f));});
        transforms1.emplace_back([](glm::mat4 m){return glm::translate(m, glm::vec3(glm::cos(glfwGetTime()*10.0f)*0.1f, 0.0f, glm::sin(glfwGetTime()*10.0f)*0.1f));});
        transforms1.emplace_back([](glm::mat4 m){return glm::scale(m, glm::vec3(0.1f, 0.1f, 0.1f));});
        transforms1.emplace_back([](glm::mat4 m){return glm::rotate(m, glm::radians(float(glfwGetTime()) * 25.0f), glm::vec3(0.0f, 1.0f, 0.0f));});
//        models.emplace_back(shrek, transforms1);
        thing.emplace_back(shrek, transforms1);
        entities.emplace_back(shrek, transforms1, 0.0f);
//        MOE::Renderer::SetModels(models);
//        MOE::Renderer::SetModels(thing);
        std::vector<std::function<void()>> esc_funcs;
        esc_funcs.emplace_back([](){glfwSetWindowShouldClose(MOE::Renderer::window, true);});
        std::vector<MOE::InputStruct> inputs;
        inputs.emplace_back(MOE::KEYS::ESCAPE, esc_funcs, true);
        std::vector<std::function<void()>> right_funcs;
        right_funcs.emplace_back([](){MOE::Renderer::camera.ProcessKeyboard(MOE::C_RIGHT, MOE::Renderer::deltaTime);});
        inputs.emplace_back(MOE::KEYS::D, right_funcs, true);
        std::vector<std::function<void()>> left_funcs;
        left_funcs.emplace_back([](){MOE::Renderer::camera.ProcessKeyboard(MOE::C_LEFT, MOE::Renderer::deltaTime);});
        inputs.emplace_back(MOE::KEYS::A, left_funcs, true);
        std::vector<std::function<void()>> up_funcs;
        up_funcs.emplace_back([](){MOE::Renderer::camera.ProcessKeyboard(MOE::C_FORWARD, MOE::Renderer::deltaTime);});
        inputs.emplace_back(MOE::KEYS::W, up_funcs, true);
        std::vector<std::function<void()>> down_funcs;
        down_funcs.emplace_back([](){MOE::Renderer::camera.ProcessKeyboard(MOE::C_BACKWARD, MOE::Renderer::deltaTime);});
        inputs.emplace_back(MOE::KEYS::S, down_funcs, true);
//        MOE::Input::SetInput(inputs);

        MOE::Physics::SetWorld();
    }

    ~SandBox() {
        MOE::Renderer::CloseWindow();
//        MOE::Renderer::ShutDown();
    }
};

MOE::Application* MOE::CreateApplication() {
    return new SandBox();
}
