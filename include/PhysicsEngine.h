//
// Created by Conni Bilham on 24/07/2023.
//

#ifndef INC_2D_ENGINE_PHYSICSENGINE_H
#define INC_2D_ENGINE_PHYSICSENGINE_H

#include <iostream>
#include "Entity_t.h"

class PhysicsEngine {
private:
    Entity_t* entity;

public:

    PhysicsEngine();
    PhysicsEngine(Entity_t* entity_i);

    void ApplyPhysics(double deltaTime);
};


#endif //INC_2D_ENGINE_PHYSICSENGINE_H
