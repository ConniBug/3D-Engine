//
// Created by Conni Bilham on 12/07/2023.
//

#include "main_scene.h"
#include "logging.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "Camera.h"
#include "glad/glad.h"
#include "../src/DebugRendering.h"

static Line* line;
void main_scene::init(Camera* camera) {
    logging::log("main_scene::init()");

    this->camera = camera;

    shaders.push_back(new Shader("shaders/vertex.glsl", "shaders/fragment.glsl"));
    shaders.push_back(new Shader("shaders/debug_line_vertex.glsl", "shaders/debug_line.frag"));

    // spawn entities at random positions
    int max_r = 100;
    int count = 1000;
    for (int i = 0; i < count; i++) {
        entity_list.push_back(new Entity_t(shaders[0]->id,
                                           glm::vec3(rand() % max_r - max_r / 2, rand() % max_r - max_r / 2, rand() % max_r - max_r / 2),
                                           glm::vec3(0.0f),
                                           glm::vec3(0.5f)));
    }

    line = new Line(shaders[1]->id,
                    glm::vec2(-1.0f, -1.0f), glm::vec2(1.0f, 1.0f),
                glm::vec2(0.0f), glm::vec2(1.0f));
    line->load();
    line->init();

    for (auto &i: entity_list) {
        i->init();
    }

    logging::log("main_scene::init()");
}

#include "PhysicsEngine.h"
void main_scene::update(double deltaTime) {
//    std::cout << "main_scene::update()" << std::endl;

    shaders[0]->apply();

    // create transformations
    glm::mat4 view          = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
    glm::mat4 projection    = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(camera->fov), (float)800 / (float)600, 0.1f, 100.0f);
    view = camera->view_matrix();

    glUniformMatrix4fv(glGetUniformLocation(shaders[0]->id, "view"), 1, GL_FALSE, &view[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(shaders[0]->id, "projection"), 1, GL_FALSE, &projection[0][0]);

    for (auto &entity : entity_list) {

        // First we want to apply physics eg gravity etc
        {
            if (!entity->physicsEngine)
                entity->physicsEngine = new PhysicsEngine(entity);
            entity->physicsEngine->ApplyPhysics(deltaTime);
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
            if (entity->position.y < 0)
                entity->position.y = 0;
        }

//        entity->scale += glm::vec3(0.0f, 0.0f, 0.1f);

        // And now im finally drawing the frame, if drew the frame
        //   before the collision we would see the blocks jittering and "glitching" up and down above y 0
        entity->draw();
    }
    line->draw();
}
