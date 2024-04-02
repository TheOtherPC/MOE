//
// Created by gru on 4/1/24.
//

#include "Entity.h"

namespace MOE {
    EntityStruct::EntityStruct(MOE::Model a, std::vector<std::function<glm::mat4(glm::mat4)>> b, float c) : model(a),
                                                                                                            transforms(
                                                                                                                    b),
                                                                                                            mass(c) {
        Renderer::modelstructs.emplace_back(model, transforms);
    }
}
