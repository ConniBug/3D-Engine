//
// Created by Conni Bilham on 10/07/2023.
//

#ifndef INC_2D_ENGINE_LOGGING_H
#define INC_2D_ENGINE_LOGGING_H

#include <iostream>

class logging {
public:
    static void log(const std::string& message);
    static void error(const std::string& message);
    static void verbose(const std::string& message);
};


#endif //INC_2D_ENGINE_LOGGING_H
