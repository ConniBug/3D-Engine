//
// Created by Conni Bilham on 15/07/2023.
//

#ifndef INC_2D_ENGINE_DEBUGRENDERING_H
#define INC_2D_ENGINE_DEBUGRENDERING_H

#include <iostream>
#include "vec2.hpp"

class Line {
private:
    unsigned int VBO, VAO, EBO;
public:
    unsigned int shader_id;

    glm::vec2 start = glm::vec2(0.0f, 0.0f);
    glm::vec2 end = glm::vec2(0.0f, 0.0f);
    glm::vec2 rotation = glm::vec2(1.0f, 1.0f);
    glm::vec2 scale = glm::vec2(1.0f, 1.0f);

    Line(unsigned int shader_id);
    Line(unsigned int shader_id, glm::vec2 start, glm::vec2 end, glm::vec2 rotation, glm::vec2 scale);

    ~Line();

    void init();

    void load();

    void draw();
};

class DebugRendering {
public:
    void draw_line();
};


#endif //INC_2D_ENGINE_DEBUGRENDERING_H
