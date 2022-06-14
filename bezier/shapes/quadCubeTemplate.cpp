#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glad/glad.h>
using namespace glm;

#include "quadCubeTemplate.hpp"


quadCubeTemplate::quadCubeTemplate(GLuint shaderprogramID){
	this->programID = shaderprogramID;
}

void quadCubeTemplate::loadTexture(GLuint mytex){
	this->texture = mytex;
}

void quadCubeTemplate::prep(){
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);
}

void quadCubeTemplate::draw(GLuint programID){

	glUseProgram(programID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(texture, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, quadCubeTemplate::vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, quadCubeTemplate::uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
    glDrawArrays(GL_QUADS, 0, 6*4);

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void quadCubeTemplate::move(float x, float y, float z){
	for(int i = 0; i < 108; i++){
		if(i%3 == 0 )g_vertex_buffer_data[i]+=x;
		if(i%3 == 1 )g_vertex_buffer_data[i]+=y;
		if(i%3 == 2 )g_vertex_buffer_data[i]+=z;
	}
}
void quadCubeTemplate::scale(float x, float y, float z){
	for(int i = 0; i < 108; i++){
		if(i%3 == 0 )g_vertex_buffer_data[i]*=x;
		if(i%3 == 1 )g_vertex_buffer_data[i]*=y;
		if(i%3 == 2 )g_vertex_buffer_data[i]*=z;
	}
}

void quadCubeTemplate::read(){
	for(int i = 2; i < 108; i+=3){
		std::cout<<"X: "<<g_vertex_buffer_data[i-2]<<"  Y:  "<<g_vertex_buffer_data[i-1]<<"  Z  "<<g_vertex_buffer_data[i]<<"\n";
	}
}
void quadCubeTemplate::cleanup(){
	glDeleteBuffers(1,&vertexbuffer);
	glDeleteBuffers(1,&uvbuffer);
}


void quadCubeTemplate::draw(GLuint programID, GLuint uniformID){

	glUseProgram(programID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    glUniform1i(texture, 0);
    glUniform1f(uniformID, .5);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, quadCubeTemplate::vertexbuffer);
	glVertexAttribPointer(
		0,                  // attribute. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, quadCubeTemplate::uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}