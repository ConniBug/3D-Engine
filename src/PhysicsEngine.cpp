//
// Created by Conni Bilham on 24/07/2023.
//

#define G -9.81

#include "PhysicsEngine.h"

PhysicsEngine::PhysicsEngine(Entity_t *entity) {
    this->entity = entity;
}

void PhysicsEngine::ApplyPhysics(double deltaTime) {
//    logging::verbose("PhysicsEngine::ApplyPhysics()");

    auto* acceleration = &this->entity->physics.engine->acceleration;
    auto* velocity = &this->entity->physics.engine->velocity;
    if(!this->entity->physics.enabled)
        return;

    acceleration->y = G;

    // Hate this but glm::vec3 doesn't have operators setup correctly
    velocity->x += acceleration->x * (float)deltaTime;
    velocity->y += acceleration->y * (float)deltaTime;
    velocity->z += acceleration->z * (float)deltaTime;

    // Hate this but glm::vec3 doesn't have operators setup correctly
    this->entity->position.x += velocity->x;
    this->entity->position.y += velocity->y;
    this->entity->position.z += velocity->z;
}