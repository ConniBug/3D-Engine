//
// Created by Conni Bilham on 12/07/2023.
//

#ifndef INC_2D_ENGINE_SCENE_H
#define INC_2D_ENGINE_SCENE_H

#include <iostream>
#include "Entity_t.h"
#include "Shader.h"
#include "Camera.h"
#include "DebugRendering.h"
#include "GLFW/glfw3.h"
#include "Storage.h"


class Scene {
public:
    Scene();
    ~Scene();

    Camera* camera;

    std::vector<DebugEntry *> debug_list;
    std::vector<Entity_t   *> entity_list;

    std::vector<Shader     *> shaders;

    int initiated = 0;

    // Master functions
    void init(Camera* camera);
    void update(double deltaTime);

    // Overridden functions
    virtual void Init(Camera* camera);
    virtual void Update(double deltaTime);
    virtual void WindowResize(int width, int height);
    virtual void HandleInput(GLFWwindow *window);
    virtual void Shutdown(int cause = 0);
    virtual void KeyPressed(GLFWwindow* window, int key, int scancode, int mods);

    virtual void HandleMouseMovement(float xoffset, float yoffset);
    virtual void HandleMouseScroll(float yoffset);

    void draw_debug();
};


#endif //INC_2D_ENGINE_SCENE_H
