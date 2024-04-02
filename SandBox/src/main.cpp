#include <iostream>
#include "MOE.h"


class SandBox : public MOE::Application {
public:
    SandBox() {
        MOE::Renderer::InitWindow("Thing");
    }
    ~SandBox() {
        MOE::Renderer::CloseWindow();
    }
};

MOE::Application* MOE::CreateApplication() {
    return new Sandbox();
}
