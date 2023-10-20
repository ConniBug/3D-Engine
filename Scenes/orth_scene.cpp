//
// Created by Conni Bilham on 25/07/2023.
//

#include "orth_scene.h"
#include "logging.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Camera.h"
#include "glad/glad.h"
#include "PhysicsEngine.h"
#include "CollisionEngine.h"
#include "DebugRendering.h"
#include "DebugRendering/DebugBox.h"

static DebugBox *box;
void orth_scene::Init(Camera *camera) {
    logging::verbose("orth_scene::init()");

    this->camera = camera;
    camera->type = CAMERA_TYPE::ORTHOGRAPHIC;

    shaders.push_back(new Shader("shaders/vertex.glsl", "shaders/cube_box.frag"));
    shaders.push_back(new Shader("shaders/debug_line_vertex.glsl", "shaders/debug_line.frag"));

    entity_list.push_back(new Entity_t(shaders[0], glm::vec3(1, -(storage->window.height / 2) + 0, 0), glm::vec3(0, 0, 0), glm::vec3(114 * 7, 10, 10)));
    entity_list[0]->physics.engine = new PhysicsEngine(entity_list[0]);

    auto A = glm::vec3(-0.5f, 0.5f, 0.0f);
    auto C = glm::vec3(0.5f, -0.5f, 0.0f);
    auto B = glm::vec3(0.5f, 0.5f, 0.0f);
    auto D = glm::vec3(-0.5f, -0.5f, 0.0f);

    debug_list.push_back(new DebugLine(shaders[1]->id, A, B));
    debug_list.push_back(new DebugLine(shaders[1]->id, B, C));
    debug_list.push_back(new DebugLine(shaders[1]->id, C, D));
    debug_list.push_back(new DebugLine(shaders[1]->id, D, A));

    for (auto &i: entity_list) {
        i->init();
    }

    logging::verbose("orth_scene::init()");
}

void orth_scene::Update(double deltaTime) {
//    std::cout << "orth_scene::update()" << std::endl;


    // create transformations
    glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection    = glm::mat4(1.0f);

    projection = glm::ortho((storage->window.width / 2.0f), -(storage->window.width / 2.0f),
                            -(storage->window.height / 2.0f), (storage->window.height / 2.0f),
                            -100.0f, 100.0f);

    view = camera->view_matrix();

    for (auto &entity: entity_list) {

        // First we want to apply physics eg gravity etc
        {
            entity->physics.engine->ApplyPhysics(deltaTime);
        }

        // I then do some custom stuff where i teleport the blocks up after 5 seconds
        //   to test physics and ensure blocks are moving when they should etc
        {
            entity->timer += deltaTime;
            if (entity->timer > 5) {
                entity->position.y = entity->position.y + 20;
                entity->timer = 0;
            }
        }

        // This is where im simulating a collision system clamping all blocks to have their center be above y 0
        {
            if (entity->position.y < -(storage->window.height / 2))
                entity->position.y = -(storage->window.height / 2);
        }

//        entity->scale = glm::vec3(camera->fov * 7, 2.1f, 2.1f);

        // And now im finally drawing the frame, if drew the frame
        //   before the collision we would see the blocks jittering and "glitching" up and down above y 0
        entity->shader->apply(view, projection);
        entity->draw();
    }

    // Render UI Elements
    {

//        shaders[1]->apply();
        draw_debug();
    }
}
void orth_scene::HandleMouseMovement(float xoffset, float yoffset) {
    const float pitch_max = 5;
    const float yaw_max = 5;

    if (camera->pitch > pitch_max)
        camera->pitch = pitch_max;
    if (camera->pitch < -pitch_max)
        camera->pitch = -pitch_max;

    if (camera->yaw < -90.f - yaw_max) {
        camera->yaw = -90.f - yaw_max;
    }
    if (camera->yaw > -90.f + yaw_max) {
        camera->yaw = -90.f + yaw_max;
    }
    logging::debug(std::to_string(camera->pitch));
}
