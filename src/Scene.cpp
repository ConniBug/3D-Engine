//
// Created by Conni Bilham on 12/07/2023.
//

#include "../include/Scene.h"

Scene::Scene() {
    std::cout << "Scene::Scene()" << std::endl;
}

Scene::~Scene() {
    std::cout << "Scene::~Scene()" << std::endl;
}

void Scene::update(double deltaTime) {
    std::cout << "Scene::update()" << std::endl;
}

void Scene::init(Camera* camera) {
    std::cout << "Scene::init()" << std::endl;
}

