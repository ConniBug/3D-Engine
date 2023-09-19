//
// Created by Conni Bilham on 10/07/2023.
//

#ifndef INC_2D_ENGINE_SHADER_H
#define INC_2D_ENGINE_SHADER_H

#include <iostream>
#include <fstream>
#include "glad/glad.h"
#include "logging.h"
#include "glm.hpp"

class Shader {
private:
    static unsigned int compile_shader(unsigned int type, const std::string& source);
    static bool check_compile_status(unsigned int shader_id);
public:
    unsigned int id;

    std::string vertex_path;
    std::string vertex_raw;

    std::string fragment_path;
    std::string fragment_raw;

    Shader(const std::string& vertex_path,
           const std::string& fragment_path
    );
    ~Shader();

    void reload();
    void load_shader(const std::string& vertex_path_r, const std::string& fragment_path_r);

    void apply(glm::mat4 view = glm::mat4(0.0f), glm::mat4 projection = glm::mat4(0.0f)) const;
};


#endif //INC_2D_ENGINE_SHADER_H
