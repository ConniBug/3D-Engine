//
// Created by Conni Bilham on 12/07/2023.
//

#ifndef INC_2D_ENGINE_MAIN_SCENE_H
#define INC_2D_ENGINE_MAIN_SCENE_H

#include "Camera.h"
#include "Scene.h"
#include "Storage.h"

#include <iostream>

class main_scene : public Scene {
public:
    void Init(Camera *camera) override;
    void Update(double deltaTime) override;
    void WindowResize(int width, int height) override;
    void HandleMouseMovement(float xoffset, float yoffset) override;
};


#endif //INC_2D_ENGINE_MAIN_SCENE_H
