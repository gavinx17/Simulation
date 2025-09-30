#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#define _USE_MATH_DEFINES

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
class Particle  {
    public:
    int height, width;
    float mass;
    Particle(int h = 50, int w = 50, float m = 10)   {
        height = h;
        width = w;
        mass = m;
    }
    void DrawParticle(float cx, float cy, float radius, int iWindowWidth = 600, int iWindowHeight = 600)  {

        glScalef(iWindowHeight/(iWindowWidth*1.0f), 1.0f, 1.0f);    
        glBegin(GL_POLYGON);
        for(double i = 0; i < 2 * M_PI; i += M_PI / 24)  {
            glVertex3f((cos(i) * radius) + cx,(sin(i) * radius) + cy, 0.0);
        }
        glEnd();
                
        //reset scaled shape
        glScalef(1.0f, 1.0f, 1.0f);
    }
};


int main(void)
{
    int height = 480, width = 640;
    Particle p[20];
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
        for(int i = 0; i < 20; i++) {
            p[i].DrawParticle(.0f + .1,.0f + .1, 0.05f);
        }
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwSetErrorCallback(error_callback);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}