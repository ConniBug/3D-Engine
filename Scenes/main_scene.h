//
// Created by Conni Bilham on 12/07/2023.
//

#ifndef INC_2D_ENGINE_MAIN_SCENE_H
#define INC_2D_ENGINE_MAIN_SCENE_H

#include "Scene.h"
#include "Camera.h"
#include "Storage.h"

#include <iostream>

class main_scene : public Scene {
public:
    void Init(Camera* camera) override;
    void Update(double deltaTime) override;
    void WindowResize(int width, int height) override;


};


#endif //INC_2D_ENGINE_MAIN_SCENE_H
