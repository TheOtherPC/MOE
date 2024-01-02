//
// Created by gru on 1/1/24.
//

#include "Application.h"

namespace MOE {
    Application::Application() {
        std::cout << "Hello Application" << std::endl;
    }
    Application::~Application() {
        std::cout << "Goodbye Application" << std::endl;
    }

    void Application::Run() {
        std::cout << "Run Application" << std::endl;
    }

}