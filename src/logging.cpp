//
// Created by Conni Bilham on 10/07/2023.
//

#include "../include/logging.h"

void logging::log(const std::string& message) {
    std::cout << message << std::endl;
}

void logging::verbose(const std::string& message) {
    log("VERBOSE: " + message);
}

void logging::error(const std::string& message) {
    log("ERROR: " + message);
}
