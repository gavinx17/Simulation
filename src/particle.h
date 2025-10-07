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
        if (y - radius <= -1.0f) {
            y = -1.0f + radius;
            vy *= -0.94f;
            vx *= 0.94f; // horizontal friction
        }
        if(y - radius >= 1.0f)    {
            vy *= -0.85; // slow down as it bounces
            y = 1.0f - radius;
        }
        vy += (gravity * dt);
        x += (vx * dt);
        y += (vy * dt);
    }
    bool CheckCollision(Particle one, Particle two) {
        float dx = one.x - two.x;
        float dy = one.y - two.y;
        float distance = sqrt(dx * dx + dy * dy);   // Distance formula
        return distance <= (one.radius + two.radius);
    }
};
#endif