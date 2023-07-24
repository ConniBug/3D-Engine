//
// Created by Conni Bilham on 12/07/2023.
//

#ifndef INC_2D_ENGINE_SCENE_H
#define INC_2D_ENGINE_SCENE_H

#include <iostream>
#include "Entity_t.h"
#include "Shader.h"
#include "Camera.h"

class Scene {
public:
    Scene();
    ~Scene();

    std::vector<Entity_t*> entity_list;
    std::vector<Shader*> shaders;

    virtual void init(Camera* camera);
    virtual void update(double deltaTime);
};


#endif //INC_2D_ENGINE_SCENE_H
