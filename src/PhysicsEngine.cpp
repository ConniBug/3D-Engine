//
// Created by Conni Bilham on 24/07/2023.
//

#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(Entity_t *entity) {
    this->entity = entity;
}

void PhysicsEngine::ApplyPhysics(double deltaTime) {
//    std::cout << "PhysicsEngine::ApplyPhysics(Entity_t* entity) Called" << std::endl;

    if(entity->physics.enabled) {
        this->entity->position.y = this->entity->position.y - (9.81 * deltaTime); // Haha gravity
    }
}