//
// Created by Conni Bilham on 10/07/2023.
//

#include <iostream>
#include "external/glad/include/glad/glad.h"
#include "external/glfw/include/GLFW/glfw3.h"
#include "Storage.h"

#include "include/Window.h"

#include "Scenes/main_scene.h"
#include "Scenes/orth_scene.h"

Storage* storage;

#define T_STR(v) std::to_string(storage->get()->version.v)
#define BUILD_STRING T_STR(major) + "." + T_STR(minor) + "." + T_STR(patch) + " Build " + T_STR(build)
int main() {
    storage = new Storage();

    if (!glfwInit()) {
        std::cout << "Failed to initialize GLFW" << std::endl;
        return -1;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);             // For Mac OS X

    storage->window.title = "d";
    storage->window.title = "";
    storage->scene_list.emplace_back(new main_scene());
    storage->scene_list.emplace_back(new main_scene());
    storage->scene_list.emplace_back(new main_scene());

    auto camera = new Camera(glm::vec3(0.0f, 0.0f, 3.0f));

    auto main_window = new Window(800, 600, storage->window.title, storage->window.fullscreen, camera);
    main_window->set_camera(camera);

    return 0;
}
