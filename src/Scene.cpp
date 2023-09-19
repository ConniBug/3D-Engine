//
// Created by Conni Bilham on 12/07/2023.
//

#include "../include/Scene.h"

Scene::Scene() {
    logging::verbose("Scene::Scene()");
}

Scene::~Scene() {
    std::cout << "Scene::~Scene()" << std::endl;
}

void Scene::update(double deltaTime) {
    if(camera == nullptr) {
        logging::error("Scene::update() - Camera is null");
        return;
    }

    this->Update(deltaTime);
}

void Scene::init(Camera* camera) {
    std::cout << "Scene::init()" << std::endl;
}

