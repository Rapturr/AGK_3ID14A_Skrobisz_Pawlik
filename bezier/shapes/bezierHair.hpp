#ifndef BEZIERHAIR_HPP
#define BEZIERHAIR_HPP


#include <glfw3.h>
#include <glad/glad.h>
#include "../common/shader.hpp"

#include <glm.hpp>

#include <iostream>
#include <gtc/matrix_transform.hpp>
#include <vector>

class BezierHair{
public:
    //mat4 view;
    //mat4 model;
    //GLSLProgram prog;
    //GLSLProgram solidProg;
    
    int t;
    /* Delta time in seconds. */
    float dt;

    float divider;
    bool direction;
    //mat4 projection;
    GLuint vaoHandle;

    void compileAndLinkShader();

	BezierHair(){};

	void bezierFunc();

    void draw(glm::mat4,Shader*);
    void setMatrices(glm::mat4,Shader*);
    void initScene(Shader*);
    void move();
    glm::vec3 windpos = glm::vec3(1.3f,2.4f,0.0f);
    float windstrength = 3.0f;
    void setwind(glm::vec3 pos){
        //windpos = pos;
        windpos = glm::vec3(1.3f,2.4f,0.0f);
    };
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

    std::vector<Vertex> hairPool;
    std::vector<Vertex> patches;
};

#endif