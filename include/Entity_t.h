//
// Created by Conni Bilham on 11/07/2023.
//

#ifndef INC_2D_ENGINE_ENTITY_T_H
#define INC_2D_ENGINE_ENTITY_T_H


#include "vec3.hpp"
#include "glad/glad.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "logging.h"
//#include "PhysicsEngine.h"

#include "Shader.h"

class PhysicsEngine;
class Entity_t {
private:
    unsigned int VBO, VAO, EBO;

public:
    double timer;
    Shader* shader;

    class Physics {
    public:
        bool enabled = false;
        PhysicsEngine* engine;
    } physics;

    glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
    glm::vec3 scale = glm::vec3(1.0f, 1.0f, 1.0f);

    Entity_t(Shader* shader);
    Entity_t(Shader* shader, glm::vec3 position, glm::vec3 rotation, glm::vec3 scale);

    ~Entity_t();

    void init();

    void load();

    void draw();
};


#endif //INC_2D_ENGINE_ENTITY_T_H
