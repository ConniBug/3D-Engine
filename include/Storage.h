//
// Created by Conni Bilham on 12/07/2023.
//

#ifndef INC_2D_ENGINE_STORAGE_H
#define INC_2D_ENGINE_STORAGE_H

#include <string>
#include "Scene.h"

class Storage {
public:
    class Version {
    public:
        unsigned int major = 0;
        unsigned int minor = 2;
        unsigned int patch = 0;

        unsigned int build = 1;
    } version;

    class Window {
    public:
        Window() {
            width = 800;
            height = 600;
            title = std::string("Engine");
            fullscreen = false;
        }

        int width;
        int height;
        std::string title;
        bool fullscreen;
    } window;

    class Config {
        float camera_fov = 45.0f;
    } config;

    std::vector<Scene*> scene_list = {};
    int loaded_scene_number = 0;
};

extern Storage* storage;


#endif //INC_2D_ENGINE_STORAGE_H