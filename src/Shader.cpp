//
// Created by Conni Bilham on 10/07/2023.
//

#include "../include/Shader.h"

//unsigned int load_shader() {
//    // Build root project path
//    const std::string root_path = std::string("/Users/connibilham/CLionProject/2D-Engine/");
//
//    // Load vertex shader from file
//    auto vertex_shader_file = std::ifstream(root_path + "shaders/vertex.glsl");
//    std::string vertex_shader_str((std::istreambuf_iterator<char>(vertex_shader_file)),
//                                  std::istreambuf_iterator<char>());
//    const char* vertex_shader = vertex_shader_str.c_str();
//
//    // Load fragment shader from file
//    auto fragment_shader_file = std::ifstream(root_path + "shaders/fragment.glsl");
//    std::string fragment_shader_str((std::istreambuf_iterator<char>(fragment_shader_file)),
//                                    std::istreambuf_iterator<char>());
//    const char* fragment_shader = fragment_shader_str.c_str();
//
//    // Compile vertex shader
//    std::cout << "Compiling vertex shader" << std::endl;
//    std::cout << vertex_shader << std::endl;
//    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
//    glShaderSource(vertex_shader_id, 1, &vertex_shader, nullptr);
//    glCompileShader(vertex_shader_id);
////    check_compile_status(vertex_shader_id);
//
//    // Compile fragment shader
//    std::cout << "Compiling fragment shader" << std::endl;
//    std::cout << fragment_shader << std::endl;
//    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
//    glShaderSource(fragment_shader_id, 1, &fragment_shader, nullptr);
//    glCompileShader(fragment_shader_id);
////    check_compile_status(fragment_shader_id);
//
//    // Link shaders
//    std::cout << "Linking shaders" << std::endl;
//    unsigned int shader_program_id = glCreateProgram();
//    glAttachShader(shader_program_id, vertex_shader_id);
//    glAttachShader(shader_program_id, fragment_shader_id);
//    glLinkProgram(shader_program_id);
//
//    // Check for linking errors
//    int success;
//    char info_log[512];
//    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &success);
//    if (!success) {
//        glGetProgramInfoLog(shader_program_id, 512, nullptr, info_log);
//        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << info_log << std::endl;
//    }
//    std::cout << "Shaders linked successfully" << std::endl;
//
//    // Delete shaders
//    glDeleteShader(vertex_shader_id);
//    glDeleteShader(fragment_shader_id);
//
//    // Use shader program
////    glUseProgram(shader_program_id);
//
//    return shader_program_id;
//}

Shader::Shader(const std::string& vertex_path, const std::string& fragment_path) {
    logging::verbose("Creating new shader" + vertex_path + " " + fragment_path);

    this->load_shader(vertex_path, fragment_path);
//    ::load_shader();
}

Shader::~Shader() {
    logging::verbose("Deleting shader " + std::to_string(this->id));
    glDeleteProgram(this->id);
}

void Shader::load_shader(const std::string& vertex_path_r, const std::string& fragment_path_r) {
    // Get current working directory from environment
    char* root_path = std::getenv("PWD");
    if (root_path == nullptr) {
        logging::error("ERROR::SHADER::CWD_NOT_FOUND");
        return;
    }
    std::string tmp = std::string(root_path) + std::string("/../");
    logging::verbose("CWD: " + std::string(tmp));

    this->vertex_path = tmp + vertex_path_r;
    this->fragment_path = tmp + fragment_path_r;

    logging::debug("Shader::load_shader() - ");
    logging::debug("-  cwd          : " + tmp);
    logging::debug("-  vertex_path  : " + this->vertex_path);
    logging::debug("-  fragment_path: " + this->fragment_path);


    // Load vertex and fragment shader from disk
    auto vertex_shader_file = std::ifstream(this->vertex_path);
    this->vertex_raw = std::string((std::istreambuf_iterator<char>(vertex_shader_file)),
                                   std::istreambuf_iterator<char>());

    auto fragment_shader_file = std::ifstream(this->fragment_path);
    this->fragment_raw = std::string((std::istreambuf_iterator<char>(fragment_shader_file)),
                                     std::istreambuf_iterator<char>());

    const char* vertex_raw = this->vertex_raw.c_str();
    const char* fragment_raw = this->fragment_raw.c_str();

    // Compile vertex shader
    logging::verbose("Compiling vertex shader");
    unsigned int vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_raw, nullptr);
    glCompileShader(vertex_shader_id);
    if(!check_compile_status(vertex_shader_id)) {
        logging::error("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
    }
    // Compile fragment shader
    logging::verbose("Compiling fragment shader");
    unsigned int fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_raw, nullptr);
    glCompileShader(fragment_shader_id);
    if(!check_compile_status(fragment_shader_id)) {
        logging::error("ERROR::SHADER::FRAGMENT::COMPILATION_FAILED");
        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
    }
    // Link shaders
    logging::verbose("Linking vertex and fragment shaders");
    this->id = glCreateProgram();
    glAttachShader(this->id, vertex_shader_id);
    glAttachShader(this->id, fragment_shader_id);
    glLinkProgram(this->id);

    // Check for linking errors
    int success;
    char info_log[512];
    glGetProgramiv(this->id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(this->id, 512, nullptr, info_log);
        logging::error("ERROR::SHADER::PROGRAM::LINKING_FAILED");
        std::cout << info_log << std::endl;
    }
    logging::debug("Shaders linked successfully");

    // Delete shaders
    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);
}

bool Shader::check_compile_status(unsigned int shader_id) {
    int success;
    char info_log[512];
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader_id, 512, nullptr, info_log);
        logging::error("ERROR::SHADER:: - " + std::to_string(shader_id) + " - ::COMPILATION_FAILED");
        std::cout << info_log << std::endl;

        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
        return false;
    }
    return true;
}

void Shader::apply(glm::mat4 view, glm::mat4 projection) const {
    glUseProgram(this->id);

    static float value = -1.0f;
    static float increment = 0.02f;
    if (value > 1.0f || value < -1.0f) {
        increment *= -1;
    }
    value += increment;
    int phaseID = glGetUniformLocation(this->id, "phase");
    glUniform1f(phaseID, value + 1);

    if(view != glm::mat4(0))
        glUniformMatrix4fv(glGetUniformLocation(this->id, "view"), 1, GL_FALSE, &view[0][0]);
    if(projection != glm::mat4(0))
        glUniformMatrix4fv(glGetUniformLocation(this->id, "projection"), 1, GL_FALSE, &projection[0][0]);
}


unsigned int Shader::compile_shader(unsigned int type, const std::string &source) {
    logging::debug("Shader::compile_shader() - " + std::to_string(type) + " - " + source);
    unsigned int shader_id = glCreateShader(type);

    const char* CSource = source.c_str();
    glShaderSource(shader_id, 1, &CSource, nullptr);
    glCompileShader(shader_id);
    check_compile_status(shader_id);
    return shader_id;
}

void Shader::reload() {
    logging::debug("Shader::reload()");
    glDeleteProgram(this->id);
    this->id = -1;
    this->load_shader(this->vertex_path, this->fragment_path);
}
