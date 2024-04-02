//
// Created by gru on 1/1/24.
//

#ifndef MOE_APPLICATION_H
#define MOE_APPLICATION_H

#include <iostream>
#include <functional>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/Renderer.h"
#include "Physics/Physics.h"
#include "Entity.h"
#include "Input.h"

namespace MOE {
    class Application {
    public:
        Application();

        virtual ~Application();

        void Run();

    };
    Application* CreateApplication();
}


#endif //MOE_APPLICATION_H
