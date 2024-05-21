#include <iostream>
#include "MOE.h"


class SandBox : public MOE::Application {
public:
    SandBox() {
//        MOE::Renderer::InitWindow("DeMOE");
        MOE::Renderer::InitWindow("DeMOE", 1000, 1550);
        MOE::Renderer::Set(MOE::Renderer::FRAMEBUFFER);
        MOE::Renderer::Set(MOE::Renderer::MOUSE);
        MOE::Renderer::Set(MOE::Renderer::SCROLL);
        Run();

    }




    static glm::mat4 Transforms(glm::mat4 m) {
        m = glm::scale(m, glm::vec3(glm::cos(float(glfwGetTime())), 1.0f, 1.0f));
        m = glm::rotate(m, glm::radians(float(glfwGetTime()) * 200.0f), glm::vec3(1.0f, 1.0f, 0.0f));
        m = glm::rotate(m, glm::radians(float(glfwGetTime()) * 500.0f), glm::vec3(0.0f, 1.0f, 1.0f));
        m = glm::translate(m, glm::vec3(0.0f, glm::sin(float(glfwGetTime())), 0.0f));
//        m = glm::rotate(m, glm::radians(float(glfwGetTime()) * -1001.0f), glm::vec3(0.0f, 0.0f, 1.0f));
//        m = glm::translate(m, glm::vec3(glm::cos(float(glfwGetTime())), glm::sin(float(glfwGetTime())), 0.0f));
        return m;
    }







    void Run() {
        MOE::Model object ("../Shrek.obj", false); /*Shrek*/
//        MOE::Model object ("../backpack.obj", true); /*Backpack*/
//        MOE::Model object("../Grass_Block.obj", false);
        std::vector<MOE::EntityStruct> entities;
        std::vector<std::function<glm::mat4(glm::mat4)>> transforms;
        transforms.emplace_back([](glm::mat4 m){return glm::translate(m,glm::vec3(0.0f, -1.0f, -5.0f));});
        transforms.emplace_back(Transforms);
        MOE::EntityStruct(object, transforms, 0.0f, glm::vec3(0.0, 0.0, 0.0));







        //Camera Inputs
        std::vector<std::function<void()>> esc_funcs;
        esc_funcs.emplace_back([]{MOE::Renderer::CloseWindow();});
        std::vector<MOE::InputStruct> inputs;
        MOE::InputStruct(MOE::KEYS::ESCAPE, esc_funcs, true);
        std::vector<std::function<void()>> right_funcs;
        right_funcs.emplace_back([](){MOE::Renderer::camera.ProcessKeyboard(MOE::C_RIGHT, MOE::Renderer::deltaTime);});
        MOE::InputStruct(MOE::KEYS::D, right_funcs, true);
        std::vector<std::function<void()>> left_funcs;
        left_funcs.emplace_back([](){MOE::Renderer::camera.ProcessKeyboard(MOE::C_LEFT, MOE::Renderer::deltaTime);});
        MOE::InputStruct(MOE::KEYS::A, left_funcs, true);
        std::vector<std::function<void()>> up_funcs;
        up_funcs.emplace_back([](){MOE::Renderer::camera.ProcessKeyboard(MOE::C_FORWARD, MOE::Renderer::deltaTime);});
        MOE::InputStruct(MOE::KEYS::W, up_funcs, true);
        std::vector<std::function<void()>> down_funcs;
        down_funcs.emplace_back([](){MOE::Renderer::camera.ProcessKeyboard(MOE::C_BACKWARD, MOE::Renderer::deltaTime);});
        MOE::InputStruct(MOE::KEYS::S, down_funcs, true);
//        MOE::Audio::loadWav("../donkey.wav");
//        MOE::Audio::playGlobal("../donkey.wav");
    }
};

MOE::Application* MOE::CreateApplication() {
    return new SandBox();
}
