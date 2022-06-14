#ifndef FLATPLANETEMPLATE_HPP
#define FLATPLANETEMPLATE_HPP

#include <glfw3.h>
#include <glad/glad.h>
#include "../common/glslprogram.h"
#include "../common/stb_image.h"

class flatPlaneTemplate{
public:
  GLfloat g_vertex_buffer_data[18] = {
		-1.0f,1.0f,-1.0f,
		-1.0f,1.0f,1.0f,
		1.0f,1.0f,-1.0f,
		1.0f,1.0f,-1.0f,
		-1.0f,1.0f,1.0f,
		1.0f,1.0f,1.0f,
	};
  GLfloat g_uv_buffer_data[12] = { 
		-1.8f,-0.5f,
		-1.8f,-0.5f,
		1.8f,-0.5f,
		1.8f,-0.5f,
		-1.8f,-0.5f,
		1.8f,-0.5f
	};
    
    GLuint vertexbuffer;
    GLuint uvbuffer;
    GLuint programID;
    GLuint texture;

    flatPlaneTemplate(GLuint);
    flatPlaneTemplate(){};

    void loadTexture(GLuint);
    void loadTexture(char*);
    void prep();
    
    void move(float,float,float);
    void scale(float,float,float);

    void draw();
    void read();
    void cleanup();
};

#endif