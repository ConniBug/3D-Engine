//
// Created by Conni Bilham on 24/07/2023.
//

#ifndef INC_2D_ENGINE_PHYSICSENGINE_H
#define INC_2D_ENGINE_PHYSICSENGINE_H

#include <iostream>
#include "Entity_t.h"

class Entity_t;
class PhysicsEngine {
public:
    Entity_t* entity{};

    glm::vec3 velocity = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 acceleration = glm::vec3(0.0f, 0.0f, 0.0f);

    PhysicsEngine(Entity_t* entity);

    void ApplyPhysics(double deltaTime);
};


#endif //INC_2D_ENGINE_PHYSICSENGINE_H
