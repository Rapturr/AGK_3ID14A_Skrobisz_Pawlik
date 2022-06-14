#ifndef PARTICLESSMOKE_HPP
#define PARTICLESSMOKE_HPP

#include "../common/shader.hpp"

#include "../common/includeonce.h"
#include "../shapes/includeShapes.hpp"
#include "../common/texture.hpp"

#include <glm.hpp>

class ParticleSmoke{
public:
    GLuint vaoHandle;
    
    GLfloat deltaTime;
    GLfloat delta;
    glm::vec2 center;

    ParticleSmoke();
    void activate();

    void live(float tt);
    void draw(Shader, glm::mat4);
    void loadTexture(GLuint);
    GLuint quadVA = 0;
    GLuint quadUV = 0;
    GLuint texture;
    bool active;
    float life, fade; // Czas życia i tempo "umierania"
    float size; // Wielkość cząstki
    float r, g, b; // Kolor R-G-B
    float x, y, z; // Pozycja X-Y-Z
    float xi, yi, zi; // Wektor ruchu X-Y-Z
    float xg, yg, zg; // Wektor grawitacji X-Y-Z
    float xr, yr, zr; // Wektor rotacji X-Y-Z
    float wind;

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
    uint32_t particleIndex = 99;
};
#endif