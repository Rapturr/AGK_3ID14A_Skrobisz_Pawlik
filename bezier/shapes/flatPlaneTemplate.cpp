#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glad/glad.h>
using namespace glm;

#include "flatPlaneTemplate.hpp"


flatPlaneTemplate::flatPlaneTemplate(GLuint shaderprogramID){
	prep();
}

void flatPlaneTemplate::loadTexture(GLuint mytex){
	this->texture = mytex;
}
void flatPlaneTemplate::loadTexture(char* src){
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	unsigned char *data = stbi_load(src, &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);
	this->texture = texture;
}

void flatPlaneTemplate::prep(){

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
    
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

    
}


void flatPlaneTemplate::draw(){

	//glUseProgram(programID);
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);
    //glUniform1i(texture, 0);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, flatPlaneTemplate::vertexbuffer);
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
	glBindBuffer(GL_ARRAY_BUFFER, flatPlaneTemplate::uvbuffer);
	glVertexAttribPointer(
		1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
		2,                                // size : U+V => 2
		GL_FLOAT,                         // type
		GL_FALSE,                         // normalized?
		0,                                // stride
		(void*)0                          // array buffer offset
	);
    glDrawArrays(GL_TRIANGLES, 0, 2*3);

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void flatPlaneTemplate::move(float x, float y, float z){
	for(int i = 0; i < 18; i++){
		if(i%3 == 0 )g_vertex_buffer_data[i]+=x;
		if(i%3 == 1 )g_vertex_buffer_data[i]+=y;
		if(i%3 == 2 )g_vertex_buffer_data[i]+=z;
	}
}
void flatPlaneTemplate::scale(float x, float y, float z){
	for(int i = 0; i < 18; i++){
		if(i%3 == 0 )g_vertex_buffer_data[i]*=x;
		if(i%3 == 1 )g_vertex_buffer_data[i]*=y;
		if(i%3 == 2 )g_vertex_buffer_data[i]*=z;
	}
}

void flatPlaneTemplate::read(){
	for(int i = 2; i < 18; i+=3){
		std::cout<<"X: "<<g_vertex_buffer_data[i-2]<<"  Y:  "<<g_vertex_buffer_data[i-1]<<"  Z  "<<g_vertex_buffer_data[i]<<"\n";
	}
}

void flatPlaneTemplate::cleanup(){
	glDeleteBuffers(1,&vertexbuffer);
	glDeleteBuffers(1,&uvbuffer);
}