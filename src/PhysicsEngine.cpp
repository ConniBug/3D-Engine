//
// Created by Conni Bilham on 24/07/2023.
//

#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine() = default;
PhysicsEngine::PhysicsEngine(Entity_t* entity_i) {
    this->entity = entity_i;
}

void PhysicsEngine::ApplyPhysics(double deltaTime) {
//        std::cout << "PhysicsEngine::ApplyPhysics(Entity_t* entity) Called" << std::endl;

    this->entity->position.y = this->entity->position.y - (9.81 * deltaTime); // Haha gravity
}