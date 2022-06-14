#ifndef KEYHOLETEMPLATE_HPP
#define KEYHOLETEMPLATE_HPP

#include <glfw3.h>
#include <glad/glad.h>

class keyHoleTemplate{
public:
    GLfloat g_vertex_buffer_data[18] = {
		-9.0f,-1.5f,-9.0f,
		-9.0f,-1.5f,9.0f,
		9.0f,-1.5f,-9.0f,
		9.0f,-1.5f,-9.0f,
		-9.0f,-1.5f,9.0f,
		9.0f,-1.5f,9.0f,
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

    keyHoleTemplate(GLuint);

    void loadTexture(GLuint);
    void prep();
    
    void move(float,float,float);
    void scale(float);

    void draw();
    void read();
    void cleanup();
};

#endif