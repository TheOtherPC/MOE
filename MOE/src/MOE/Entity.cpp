//
// Created by gru on 4/1/24.
//

#include "Entity.h"

namespace MOE {
    EntityStruct::EntityStruct(MOE::Model a, std::vector<std::function<glm::mat4(glm::mat4)>> b, float c, glm::vec3 d) : model(a), transforms(b), mass(c), pos(d){
        Renderer::modelstructs.emplace_back(model, transforms);
        Physics::AddObject(model.boundingBox, mass, pos);
        Entity::entities.emplace_back(*this);
    }

    std::vector<EntityStruct> Entity::entities;
    void Entity::updatePositions() {
        std::vector<glm::vec3> pos = Physics::GetPositions();
        for(int i = 0; i < pos.size(); i++) {
            pos[i].x = entities[i].pos.x;
            pos[i].y = entities[i].pos.y;
            pos[i].z = entities[i].pos.z;
        }
    }
}
