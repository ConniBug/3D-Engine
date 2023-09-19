//
// Created by Conni Bilham on 18/09/2023.
//

#ifndef INC_2D_ENGINE_DEBUGBOX_H
#define INC_2D_ENGINE_DEBUGBOX_H

#include "vec3.hpp"
#include "DebugEntry.h"

class DebugBox : public DebugEntry {
public:
    glm::vec3 start = glm::vec3(0.0f, 0.0f, 0.f);
    glm::vec3 end = glm::vec3(0.0f, 0.0f, 0.f);

    glm::vec3 size = glm::vec3(0.0f, 0.0f, 0.f);

    DebugBox(unsigned int shader_id, glm::vec3 start, glm::vec3 end);

    ~DebugBox();

    void init() override;

    void load() override;

    void draw() override;
};

#endif //INC_2D_ENGINE_DEBUGBOX_H
