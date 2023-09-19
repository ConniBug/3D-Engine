//
// Created by Conni Bilham on 28/08/2023.
//

#include "DebugRendering.h"
#include "DebugRendering/DebugBox.h"
#include "glad/glad.h"

DebugBox::DebugBox(unsigned int shader_id, glm::vec3 start, glm::vec3 end) {
    this->shader_id = shader_id;
    this->start = start;
    this->end = end;
}

DebugBox::~DebugBox() {
    std::cout << "Box::~Box()" << std::endl;
}

void DebugBox::load() {
    std::cout << "Box::load()" << std::endl;
    float vertices[] = {
            start.x, start.y, 0.0f,
            end.x, start.y, 0.0f,
            end.x, end.y, 0.0f,
            start.x, end.y, 0.0f
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

void DebugBox::draw() {
    // Apply shader
    glUseProgram(shader_id);

    float vertices[] = {
            start.x, start.y, 0.0f,
            end.x, start.y, 0.0f,
            end.x, end.y, 0.0f,
            start.x, end.y, 0.0f
    };

    // Bind VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(VAO);
    glDrawArrays(GL_LINE_LOOP, 0, 4);
}

void DebugBox::init() {
    std::cout << "Box::init()" << std::endl;
}
