//
// Created by Conni Bilham on 10/07/2023.
//

#ifndef INC_2D_ENGINE_WINDOW_H
#define INC_2D_ENGINE_WINDOW_H

#include <iostream>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Shader.h"
#include "Storage.h"
#include "Scene.h"
#include "Camera.h"
#include "../include/Shader.h"
#include "../include/logging.h"

#include <iostream>

class Window {

public:
    int width;
    int height;
    std::string title;

    Scene* loaded_scene;
    Camera* camera;

    Window(int width, int height, std::string title, int fullscreen, Camera* camera_n);

    ~Window();

    void set_camera(Camera* camera_n);
    void set_window_title(std::string title_n);

    static void window_size_callback(GLFWwindow* window, int width, int height);
    void window_loop_callback(GLFWwindow* window);

    void handle_input(GLFWwindow* window);

    void mouse_callback(GLFWwindow* window, double xposIn, double yposIn);
    void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
};


#endif //INC_2D_ENGINE_WINDOW_H
