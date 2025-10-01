#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

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
    float x, y;       // current position
    float vx, vy;     // velocity
    float radius;
    float gravity = -.980665f;
    float force = .98f;
    Particle(float startX, float startY, float r)
        : x(startX), y(startY), vx(0.0f), vy(0.0f), radius(r) {}
    void DrawParticle()  {
        glBegin(GL_POLYGON);
        for(double i = 0; i < 2 * M_PI; i += M_PI / 24)  {
            glVertex3f((cos(i) * radius) + x,(sin(i) * radius) + y, 0.0);
        }
        glEnd();
    }
    void Update(float dt)   {
        if(x + radius < -1)    {
            vx *= -0.8f;
        }
        if(x + radius > 1)    {
            vx *= -0.8f;
        }
        if(y + radius < -1)    {
            vy *= -0.85; // slow down as it bounces
            y = -1.0f + radius;
            if(fabs(vy + radius) < 0.01f) vy = 0.0f; // snap to the bottom when threshold met
        }
        vy += (gravity * dt);
        x += vx * dt;
        y += vy * dt;
    }
};


int main(void)
{
    int height = 720, width = 1280;
    Particle p(0.0f, 0.0f, 0.03f);
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
        p.Update(0.00075f);
        // check input
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
            p.vx = 0.5f; p.vy = 0.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
            p.vx = -0.5f; p.vy = 0.0f;
        }
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
            p.vx = 0.0f; p.vy = 0.5;
        }
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
            p.vx = -0.5f; p.vy = -0.5;
        }
        p.Update(0.001f);
        p.DrawParticle();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    

    glfwSetErrorCallback(error_callback);
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}