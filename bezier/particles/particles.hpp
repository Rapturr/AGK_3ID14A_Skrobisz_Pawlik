#ifndef PARTICLES_HPP
#define PARTICLES_HPP

#include "../common/shader.hpp"

#include "../common/includeonce.h"
#include "../shapes/includeShapes.hpp"
#include "../common/texture.hpp"

#include <glm.hpp>


class Particle{
public:
    GLuint vaoHandle;
    
    GLfloat deltaTime;
    GLfloat delta;
    
    Particle();
    void activate();

    void live(float tt);
    void draw(Shader);
    GLuint quadVA = 0;
    bool active;
    float life, fade; // Czas życia i tempo "umierania"
    float size; // Wielkość cząstki
    float r, g, b; // Kolor R-G-B
    float x, y, z; // Pozycja X-Y-Z
    float xi, yi, zi; // Wektor ruchu X-Y-Z
    float xg, yg, zg; // Wektor grawitacji X-Y-Z
    float xr, yr, zr; // Wektor rotacji X-Y-Z

    struct Vertex
    {
        glm::vec3 Position;
        glm::vec3 Velocity;
		glm::vec4 Color;
		float Rotation = 0.0f;
		float SizeBegin, SizeEnd;

		float LifeTime = 1.0f;
		float LifeRemaining = 0.0f;

		bool Active = false;
    };
    
    void Emit(const Vertex& particleProps);
    std::vector<Vertex> particlePool;
};

#endif