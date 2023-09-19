//
// Created by Conni Bilham on 18/09/2023.
//

#ifndef INC_2D_ENGINE_DEBUGENTRY_H
#define INC_2D_ENGINE_DEBUGENTRY_H

class DebugEntry {
public:
    unsigned int VBO{}, VAO{}, EBO{};
    unsigned int shader_id{};

    DebugEntry();
    ~DebugEntry();

    virtual void init();

    virtual void load();

    virtual void draw();
};

#endif //INC_2D_ENGINE_DEBUGENTRY_H
