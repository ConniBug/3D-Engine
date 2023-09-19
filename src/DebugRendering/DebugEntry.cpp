//
// Created by Conni Bilham on 18/09/2023.
//

#include <iostream>
#include "../include/DebugRendering/DebugEntry.h"

DebugEntry::DebugEntry() = default;

DebugEntry::~DebugEntry() = default;

void DebugEntry::init() {
    std::cout << "DebugEntry::init()" << std::endl;
}

void DebugEntry::load() {
    std::cout << "DebugEntry::load()" << std::endl;
}

void DebugEntry::draw() {
    std::cout << "DebugEntry::draw()" << std::endl;
}