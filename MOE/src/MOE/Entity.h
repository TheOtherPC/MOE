//
// Created by gru on 4/1/24.
//

#ifndef MOE_ENTITY_H
#define MOE_ENTITY_H

#include<functional>
#include<iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Renderer/Renderer.h"
#include "Physics/Physics.h"

namespace MOE {
    struct EntityStruct {
        Model model;
        std::vector<std::function<glm::mat4(glm::mat4)>> transforms;
        float mass;

        EntityStruct(Model, std::vector<std::function<glm::mat4(glm::mat4)>>, float);
    };
}


#endif //MOE_ENTITY_H
