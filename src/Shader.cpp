//
// Created by Conni Bilham on 10/07/2023.
//

#include "../include/Shader.h"

Shader::Shader(const std::string &vertex_path, const std::string &fragment_path) {
    logging::verbose("Creating new shader " + vertex_path + " " + fragment_path);

    this->load_shader(vertex_path, fragment_path);
    // ::load_shader();
}

Shader::~Shader() {
    logging::verbose("Deleting shader " + std::to_string(this->id));
    glDeleteProgram(this->id);
}

void Shader::load_shader(const std::string &vertex_path_r, const std::string &fragment_path_r) {
    // Get current working directory from environment vars
    char *root_path = std::getenv("PWD");
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

    // Compile vertex shader
    logging::debug("Compiling vertex shader");
    unsigned int vertex_shader_id = compile_shader(GL_VERTEX_SHADER, this->vertex_raw);

    // Compile fragment shader
    logging::debug("Compiling fragment shader");
    unsigned int fragment_shader_id = compile_shader(GL_FRAGMENT_SHADER, this->fragment_raw);

    // Link shaders
    this->id = Shader::link_shaders(fragment_shader_id, vertex_shader_id);
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

    if (view != glm::mat4(0))
        glUniformMatrix4fv(glGetUniformLocation(this->id, "view"), 1, GL_FALSE, &view[0][0]);
    if (projection != glm::mat4(0))
        glUniformMatrix4fv(glGetUniformLocation(this->id, "projection"), 1, GL_FALSE, &projection[0][0]);
}

std::string ShaderTypeRaw(unsigned int type) {
    switch (type) {
        case (GL_VERTEX_SHADER):
            return "VERTEX";
        case (GL_FRAGMENT_SHADER):
            return "FRAGMENT";
        default:
            return "UNKNOWN_TYPE";
    }
}

unsigned int Shader::compile_shader(unsigned int type, const std::string &source) {
    auto type_e = ShaderTypeRaw(type);
    logging::verbose("Shader::compile_shader() - " + type_e);
    unsigned int shader_id = glCreateShader(type);

    const char *CSource = source.c_str();
    glShaderSource(shader_id, 1, &CSource, nullptr);
    glCompileShader(shader_id);
    if (!check_compile_status(shader_id)) {
        logging::error("ERROR::SHADER::" + type_e + "::COMPILATION_FAILED");

        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
    }
    return shader_id;
}

unsigned int Shader::link_shaders(unsigned int fragment_id, unsigned int vertex_id) {
    // Link shaders
    logging::verbose("Linking vertex and fragment shaders");
    auto id = glCreateProgram();
    glAttachShader(id, vertex_id);
    glAttachShader(id, fragment_id);
    glLinkProgram(id);

    // Check for linking errors
    int success;
    char info_log[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, nullptr, info_log);
        logging::error("ERROR::SHADER::PROGRAM::LINKING_FAILED");
        std::cout << info_log << std::endl;

        std::cout << "Press enter to continue..." << std::endl;
        std::cin.get();
    } else
        logging::debug("Shaders linked successfully");

    // Delete shaders
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
    return id;
}

void Shader::reload() {
    logging::debug("Shader::reload()");
    glDeleteProgram(this->id);
    this->id = -1;
    this->load_shader(this->vertex_path, this->fragment_path);
}
