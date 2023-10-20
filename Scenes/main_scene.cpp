//
// Created by Conni Bilham on 12/07/2023.
//

#include "main_scene.h"
#include "logging.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Camera.h"
#include "glad/glad.h"
#include "../include/PhysicsEngine.h"
#include "DebugRendering/DebugBox.h"

void main_scene::Init(Camera *camera) {
    logging::verbose("main_scene::init()");

    this->camera = camera;
    camera->type = CAMERA_TYPE::PERSPECTIVE;

    shaders.push_back(new Shader("shaders/vertex.glsl", "shaders/fragment.glsl"));
    shaders.push_back(new Shader("shaders/debug_line_vertex.glsl", "shaders/debug_line.frag"));

    // spawn entities at random positions
//    int max_r = 100;
//    int count = 100000;
//    for (int i = 0; i < count; i++) {
//        auto entity = new Entity_t(shaders[0],
//                                   glm::vec3(rand() % max_r - max_r / 2, rand() % max_r - max_r / 2, rand() % max_r - max_r / 2),
//                                   glm::vec3(0.0f),
//                                   glm::vec3(0.5f));
//        entity->physics.engine = new PhysicsEngine(entity);
//        entity->physics.enabled = i % 10;
//        entity_list.push_back(entity);
//    }
    auto entity = new Entity_t(shaders[0],
                               glm::vec3(0, 0, 0),
                               glm::vec3(0.0f),
                               glm::vec3(0.5f));
    entity->physics.engine = new PhysicsEngine(entity);
    entity->physics.enabled = 0;
    entity_list.push_back(entity);


    for (auto &i: entity_list) {
        i->init();
    }

    logging::verbose("main_scene::init()");
}

void main_scene::Update(double deltaTime) {
    // create transformations
    glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection    = camera->getProjectionMatrix(storage->window.width, storage->window.height);

    view *= camera->view_matrix();


    for (auto &entity : entity_list) {
        // First we want to apply physics e.g. gravity etc
        {
            entity->physics.engine->ApplyPhysics(deltaTime);
        }

        // I then do some custom stuff where I teleport the blocks up after 5 seconds
        //   to test physics and ensure blocks are moving when they should etc
        {
            entity->timer += deltaTime;
            if (entity->timer > 2) {
//                entity->position.y = (rand() % 200) / 10;
                entity->timer = 0;
            }
        }

        // This is where im simulating a collision system clamping all blocks to have their center be above y 0
        {
//            if (entity->position.y < 0)
//                entity->position.y = 0;
        }

//        entity->scale += glm::vec3(0.0f, 0.0f, 0.1f);

        // And now im finally drawing the frame, if drew the frame
        //   before the collision we would see the blocks jittering and "glitching" up and down above y 0
        entity->shader->apply(view, projection);
        entity->draw();
    }

    this->draw_debug();
}

void main_scene::WindowResize(int width, int height) {

void main_scene::HandleMouseMovement(float xoffset, float yoffset) {
    const float pitch_max = 89;
    if (camera->pitch < -pitch_max) {
        camera->pitch = -pitch_max;
    }
    if (camera->pitch > pitch_max) {
        camera->pitch = pitch_max;
    }
}
