//
// Created by Conni Bilham on 25/07/2023.
//

#ifndef INC_2D_ENGINE_ORTH_SCENE_H
#define INC_2D_ENGINE_ORTH_SCENE_H

#include "Camera.h"
#include "Scene.h"
#include "Storage.h"

class orth_scene : public Scene {
public:
    void Init(Camera *camera) override;
    void Update(double deltaTime) override;

    void HandleMouseMovement(float xoffset, float yoffset) override;
};


#endif//INC_2D_ENGINE_ORTH_SCENE_H
