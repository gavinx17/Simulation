#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>
#include "particle.h"

#define max_size 1
#define min_size -1

using namespace std;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

int main(void)
{
    const int num = 5;
    int particleNumber = 0;
    int height = 720, width = 1280;
    Particle p[num];
    for (int i = 0; i < num; i++) {
        float startX = ((float)rand() / RAND_MAX) * (max_size - (min_size)) - max_size; // random between -1 and 1
        float startY = ((float)rand() / RAND_MAX) * (max_size - (min_size)) - max_size;
        p[i] = Particle(startX, startY, 0.03f);
    }
    // Initialize GLFW
    if (!glfwInit())
    {
        cerr << "Failed to initialize GLFW\n";
        return -1;
    }

    // Create window
    GLFWwindow* window = glfwCreateWindow(width, height, "Simulation", NULL, NULL);
    if (!window)
    {
        cerr << "Failed to create window\n";
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Main loop
    while (!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        glColor3f(0.078f, 0.75f, 0.078f);
        for(int i = 0; i < num; i++)   {
            p[i].DrawParticle();
            p[i].Update(0.001f);
            for (int j = i + 1; j < num; j++) {
                if (p[i].CheckCollision(p[i], p[j])) {
                    p[i].vx += 0.006f;
                    p[j].vx -= 0.006f;
                    p[i].vy += 0.006f;
                    p[j].vy -= 0.006f;
                }
            }
        }
            // check input
            if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
                p[particleNumber].vx += 0.006f;
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
                p[particleNumber].vx += -0.006f;
            }
            if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)  {
                p[particleNumber].vy += 0.005f;
              //  if(p[particleNumber].y - p[particleNumber].radius <= -1.0f)
                p[particleNumber].y += 0.005f;
            }
            static bool tabPressed = false;
            if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) {
                if (!tabPressed) {
                    particleNumber = (particleNumber + 1) % num;
                    tabPressed = true;
                }
            } else {
                tabPressed = false;
            }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    

    glfwSetErrorCallback(error_callback);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}