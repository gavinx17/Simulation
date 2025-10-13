#ifndef BLOCK_H
#define BLOCK_H

#include "particle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>

class Block {
    public:
    float height, width, mass, x, y;
    unsigned int VAO, VBO, shaderProgram;
    float vertices[18] = {
        -1.0f, -0.8f, 0.0f,  // top left
        -0.8f, -0.8f, 0.0f,  // top right
        -0.8f, -1.0f, 0.0f,  // bottom right

        -0.8f, -1.0f, 0.0f,  // bottom right
        -1.0f, -1.0f, 0.0f,  // bottom left
        -1.0f, -0.8f, 0.0f   // top left
    };
    const char* vertexShaderSource = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;
        void main() {
            gl_Position = vec4(aPos, 1.0);
        }
    )";

    const char* fragmentShaderSource = R"(
        #version 330 core
        out vec4 FragColor;
        void main() {
            FragColor = vec4(1.0, 0.5, 0.2, 1.0);
        }
    )";
    Block() : x(0), y(0), height(0.0f), width(0.0f) {}


    Block(float startX, float startY, float startHeight, float startWidth)
        : x(startX), y(startY), height(startHeight), width(startWidth) {}
    static bool CheckCollision(Particle& p, Block& b);
    void InitBlock();
    void DrawBlock();
};
#endif