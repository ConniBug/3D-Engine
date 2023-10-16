//
// Created by Conni Bilham on 16/10/2023.
//

#ifndef INC_2D_ENGINE_DEBUGLINE_H
#define INC_2D_ENGINE_DEBUGLINE_H

#include <iostream>
#include "vec3.hpp"
#include "DebugRendering/DebugEntry.h"

class DebugLine : public DebugEntry {
public:
    glm::vec3 start = glm::vec3(0.0f, 0.0f, 0.f);
    glm::vec3 end = glm::vec3(0.0f, 0.0f, 0.f);

    DebugLine(unsigned int shader_id, glm::vec3 start, glm::vec3 end);

    ~DebugLine();

    void init() override;

    void load() override;

    void draw() override;
};


#endif //INC_2D_ENGINE_DEBUGLINE_H
