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
        glm::vec3 pos;
        EntityStruct(Model, std::vector<std::function<glm::mat4(glm::mat4)>>, float, glm::vec3);
    };

    class Entity {
    public:
        static void updatePositions();
        static std::vector<EntityStruct> entities;

    };
}


#endif //MOE_ENTITY_H
