//
// Created by Conni Bilham on 15/07/2023.
//

#include "DebugRendering.h"
#include "glad/glad.h"

Line::Line(unsigned int shader_id) {
    std::cout << "Line::Line()" << std::endl;
    this->shader_id = shader_id;
}

Line::Line(unsigned int shader_id, glm::vec2 start, glm::vec2 end, glm::vec2 rotation, glm::vec2 scale) {
    std::cout << "Line::Line()" << std::endl;
    this->shader_id = shader_id;
    this->start = start;
    this->end = end;
    this->rotation = rotation;
    this->scale = scale;

    load();
}

Line::~Line() {
    std::cout << "Line::~Line()" << std::endl;
}

void Line::load() {
std::cout << "Line::load()" << std::endl;
    float vertices[] = {
            start.x, start.y, 0.0f,
            end.x, end.y, 0.0f
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind VAO
    glBindVertexArray(VAO);

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Set vertex attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) nullptr);
    glEnableVertexAttribArray(0);

    // Unbind VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind VAO
    glBindVertexArray(0);
}

void Line::draw() {
//    std::cout << "Line::draw()" << std::endl;

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);

}
void Line::init() {
    std::cout << "Line::init()" << std::endl;
}

