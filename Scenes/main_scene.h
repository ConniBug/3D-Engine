//
// Created by Conni Bilham on 12/07/2023.
//

#ifndef INC_2D_ENGINE_MAIN_SCENE_H
#define INC_2D_ENGINE_MAIN_SCENE_H

#include "Scene.h"
#include "Camera.h"

#include <iostream>

class main_scene : public Scene {
public:
    Camera* camera;

    void init(Camera* camera) override;
    void update(double deltaTime) override;
};


#endif //INC_2D_ENGINE_MAIN_SCENE_H
