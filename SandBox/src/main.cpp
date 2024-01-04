#include <iostream>
#include "MOE.h"
#include "MOE/Renderer/Renderer.h"


class SandBox : public MOE::Application {
public:
    SandBox() {
        MOE::Renderer::Init();
        MOE::Renderer::InitWindow("Thing");
    }
    ~SandBox() {
        MOE::Renderer::CloseWindow();
        MOE::Renderer::ShutDown();
    }
};

MOE::Application* MOE::CreateApplication() {
    auto* sandbox = new SandBox();
    std::cin.get();
    delete sandbox;
}
