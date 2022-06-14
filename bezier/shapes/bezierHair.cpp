#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glad/glad.h>
#include <vector>
#include <cmath>
#include <ctgmath>
using namespace glm;

#include "bezierhair.hpp"

#define MAX_PART 2000 // Liczba cząstek
// Odstęp (sekundy) między aktywacjami kolejnych cząstek:
#define ACTIVATE_TIME 0.05
// Losowanie liczby w zakresie 0..1:
#define F_RAND() ((float)rand()/RAND_MAX)

void BezierHair::draw(glm::mat4 MVP, Shader *shader){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    shader->setMat4("MVP", MVP);
    shader->setVec3("windPos",windpos);
    for (auto& particle : hairPool)
	{
        glBindVertexArray(vaoHandle);
        if(direction)
            divider+=0.001f;
        else
            divider-=0.001f;
        //prog.use();
        //prog.setUniform("MVP", MVP);
        //prog.setUniform("MVP", projection * mv);
        double amp=1;
        double freq = 2;
        //double t=0.0;
        float y = amp * cos(2 * glm::pi<float>() * freq * divider*particle.Rotation );
        //float diff = sin(M_PI_2/divider);
        float additional = cos(glm::pi<float>() /divider*particle.Rotation);
        /*prog.setUniform("sin", y);
        prog.setUniform("additional", additional);
        prog.setUniform("posoff",particle.Position);
        prog.setUniform("positionOffset",particle.Position);*/

        shader->setFloat("sin", y);
        shader->setFloat("additional", additional);
        shader->setVec3("posoff",particle.Position);
        shader->setVec3("hpos",particle.Position);
        shader->setVec3("positionOffset",particle.Position);

        if(divider > 36)
            direction = !direction;
        // Draw the curve
        glDrawArrays(GL_PATCHES, 0, 4);

        // Draw the control points
        //solidProg.use();
        //glDrawArrays(GL_POINTS, 0, 4);
        
    }
    glFinish();
}

void BezierHair::move()
{
    for (auto& particle : hairPool)
	{
        /*particle.Position.x = particle.Position.x+=xi * tt;
        particle.Position.y = particle.Position.y+=yi * tt;
        particle.Position.z = particle.Position.z+=zi * tt;*/
        /*if(particle.Active){
            particle.Position.x += particle.Velocity.x * 0.4f;
            particle.Position.y += particle.Velocity.y;
            particle.Position.z += particle.Velocity.z * 0.4f;
        }*/
        /*deltaTime = glfwGetTime();
        if(deltaTime - delta > ACTIVATE_TIME) */
        if (!particle.Active)
		{
            //delta = glfwGetTime();
			//particle.Active = false;

            //activate();

            particle.Active = true;
            //particle.Position = glm::vec3(0.0f,-0.5f,0.0f);
            particle.Position = glm::vec3(F_RAND()*1.6f-0.3+1.0,1.6f,F_RAND()*1.6-0.7f);
            //particle.Position = glm::vec3(x,y,z);
            particle.Rotation = F_RAND() * 0.0002f+0.002f * glm::pi<float>();

            // Velocity
            //particle.Velocity = glm::vec3(xi*tt,yi*tt,zi*tt);
            particle.Velocity = glm::vec3(0.1f,0.1f,0.1f);

            particle.LifeRemaining = 1.0f;

			continue;
		}
        particle.LifeRemaining -= 0.01*2;
    }
    for(int i = 0; i < 100; i++){
        Vertex v;
        v.Active = true;
        v.Position = glm::vec3(F_RAND()*0.1f+1.3+1.0,1.55f,F_RAND()*1.2-0.5f);
        v.Rotation = F_RAND() * 0.0002f+0.002f * glm::pi<float>();
        v.Velocity = glm::vec3(0.1f,0.1f,0.1f);
        v.LifeRemaining = 1.0f;
        hairPool.push_back(v);
    }
    for(int i = 0; i < 100; i++){
        Vertex v;
        v.Active = true;
        v.Position = glm::vec3(F_RAND()*0.1f-0.5+1.0,1.5f,F_RAND()*1.2-0.5f);
        v.Rotation = F_RAND() * 0.0002f+0.002f * glm::pi<float>();
        v.Velocity = glm::vec3(0.1f,0.1f,0.1f);
        v.LifeRemaining = 1.0f;
        hairPool.push_back(v);
    }

    for(int i = 0; i < 100; i++){
        Vertex v;
        v.Active = true;
        v.Position = glm::vec3(F_RAND()*0.1f+1.4+1.0,1.5f,F_RAND()*1.-0.5f);
        v.Rotation = F_RAND() * 0.0002f+0.002f * glm::pi<float>();
        v.Velocity = glm::vec3(0.1f,0.1f,0.1f);
        v.LifeRemaining = 1.0f;
        hairPool.push_back(v);
    }
    for(int i = 0; i < 100; i++){
        Vertex v;
        v.Active = true;
        v.Position = glm::vec3(F_RAND()*0.1f-0.4+1.0,1.55f,F_RAND()*1.-0.5f);
        v.Rotation = F_RAND() * 0.0002f+0.002f * glm::pi<float>();
        v.Velocity = glm::vec3(0.1f,0.1f,0.1f);
        v.LifeRemaining = 1.0f;
        hairPool.push_back(v);
    }
}

void BezierHair::initScene( Shader *shader){
    glEnable(GL_DEPTH_TEST);
    hairPool.resize(MAX_PART);

    divider = 0.0f;

    //float c = 3.5f;
    //projection = glm::ortho(-0.4f * c, 0.4f * c, -0.3f *c, 0.3f*c, 0.1f, 100.0f);
    glPointSize(10.0f);
    // Set up patch VBO
    float v[] = {
    -1.0f,-1.0f,-1.0f, 
    -1.0f,-0.98f,-1.2f, 
    -1.0f,-1.0f,-1.5f, 
    -1.0f,-1.2f,-2.8f};

    GLuint vboHandle;
    glGenBuffers(1, &vboHandle);

    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
    glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(float), v, GL_STATIC_DRAW);
    // Set up patch VAO
    glGenVertexArrays(1, &vaoHandle);
    glBindVertexArray(vaoHandle);
    glBindBuffer(GL_ARRAY_BUFFER, vboHandle);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    // Set the number of vertices per patch.  IMPORTANT!!
    glPatchParameteri( GL_PATCH_VERTICES, 4);

    
    shader->use();
    shader->setInt("NumSegments", 50);
    shader->setInt("NumStrips", 1);
    shader->setVec4("LineColor", vec4(0.2f,0.3f,0.1f,0.9f));
    shader->setVec3("windPos",windpos);
    shader->setFloat("windStr", windstrength);

    //solidProg.use();
    //solidProg.setUniform("Color", vec4(0.5f,1.0f,1.0f,1.0f));
}

void BezierHair::compileAndLinkShader(){
        
}
