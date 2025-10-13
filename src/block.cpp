#include "block.h"
#include "particle.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <algorithm>

using namespace std;

bool Block::CheckCollision(Particle& p, Block& b) {
    float halfWidth = b.width / 2.0f;
    float halfHeight = b.height / 2.0f;
    float left = b.x - halfWidth;
    float right = b.x + halfWidth;
    float top = b.y + halfHeight;
    float bottom = b.y - halfHeight;

    float closestX = max(left, min(p.x, right));
    float closestY = max(bottom, min(p.y, top));

    float dx = p.x - closestX;
    float dy = p.y - closestY;

    return (dx * dx + dy * dy) < (p.radius * p.radius);
}
void Block::InitBlock() {
    float minX = vertices[0];
    float maxX = vertices[0];
    float minY = vertices[1];
    float maxY = vertices[1];

    // Loop through vertex array to find min/max
    for (int i = 0; i < 18; i += 3) {
        if (vertices[i] < minX) minX = vertices[i];
        if (vertices[i] > maxX) maxX = vertices[i];
        if (vertices[i + 1] < minY) minY = vertices[i + 1];
        if (vertices[i + 1] > maxY) maxY = vertices[i + 1];
    }

    // Set block properties
    x = (minX + maxX) / 2.0f;          // center X
    y = (minY + maxY) / 2.0f;          // center Y
    width = maxX - minX;               // total width
    height = maxY - minY;              // total height
    // Create VAO and VBO once
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Build shaders once
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    // Delete temporary shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Set up attribute pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}
void Block::DrawBlock() {
    glUseProgram(shaderProgram);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}