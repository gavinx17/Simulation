#include <iostream>
#include <math.h>
#include <vector>
#include <GLFW/glfw3.h>
#ifndef PARTICLE_H
#define PARTICLE_H

class Particle  {
    public:
    float x, y;       // current position
    float vx, vy;     // velocity
    float radius;
    float gravity = -.980665f;
    float force = .98f;
    Particle() : x(0), y(0), vx(0.0f), vy(0.0f), radius(0) {}
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
        if(x - radius <= -1.0f)    {
            vx *= -0.8f;
            x = -1.0f + radius;
        }
        if(x + radius >= 1.0f)    {
            vx *= -0.8f;
            x = 1.0f - radius;
        }
        if(y - radius <= -1.0f)    {
            vy *= -0.85; // slow down as it bounces
            y = -1.0f + radius;
            if(fabs(vy + radius) < 0.01f) vy = 0.0f; // snap to the bottom when threshold met
        }
        vy += (gravity * dt);
        x += vx * dt;
        y += vy * dt;
    }
};
#endif