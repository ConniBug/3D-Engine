//
// Created by Conni Bilham on 12/07/2023.
//

#include "../include/Scene.h"

Scene::Scene() {
    logging::verbose("Scene::Scene()");
}

Scene::~Scene() {
    this->Shutdown(0);

    for (auto *entry: debug_list)
        delete entry;
    for (auto *entry: entity_list)
        delete entry;
    for (auto *shader: shaders)
        delete shader;
}

void Scene::update(double deltaTime) {
    if (camera == nullptr) {
        logging::error("Scene::update() - Camera is null");
        return;
    }

    this->Update(deltaTime);
}

void Scene::init(Camera *camera, Window *window) {
    if (initiated == 0) {
        initiated = 1;
    } else {
        logging::error("Scene::init() - Scene already initiated");
        return;
    }
    //    logging::debug("Scene::init()");
    this->Init(camera);
    this->main_window = window;
}

// DO NOT EDIT - WONT DO ANYTHING - Overridden

void Scene::Init(Camera *camera) {
    logging::verbose("Scene::Init()");
}

void Scene::Update(double deltaTime) {
    logging::verbose("Scene::Update()");
}

void Scene::WindowResize(int width, int height) {
    logging::verbose("Scene::WindowResize()");
}

void Scene::HandleInput(GLFWwindow *window) {
    //    logging::verbose("Scene::HandleInput()");
}

void Scene::Shutdown(int cause) {
    logging::verbose("Scene::Shutdown(" + std::to_string(cause) + ")");
}

void Scene::KeyPressed(GLFWwindow *window, int key, int scancode, int mods) {
    logging::verbose("Scene::KeyPressed()");
}

void Scene::HandleMouseMovement(float xoffset, float yoffset) {
    logging::verbose("Scene::HandleMouseMovement(X Offset " + std::to_string(xoffset) + ", Y Offset " + std::to_string(yoffset) + ")");
}

void Scene::HandleMouseScroll(float yoffset) {
    logging::verbose("Scene::HandleMouseScroll(Y Offset " + std::to_string(yoffset) + ")");
}


////////////////////////////

void Scene::draw_debug() {
    // Draw debug entities
    for (auto *entry: debug_list) {
        entry->draw();
    }
}
