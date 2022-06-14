#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glad/glad.h>
using namespace glm;

#include "skyBox.hpp"


skyBox::skyBox(GLuint shaderprogramID){
	this->programID = shaderprogramID;
}

void skyBox::loadTexture(GLuint mytex){
	this->texture = mytex;
}
void skyBox::loadTexture(){
	GLuint cubemapTexture = loadCubemap(faces);
	this->texture = cubemapTexture;
}
void skyBox::loadTexture(char* src){
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

void skyBox::prep(){

	glGenVertexArrays(1, &skyboxVAO);
    glGenBuffers(1, &skyboxVBO);
    glBindVertexArray(skyboxVAO);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), &g_vertex_buffer_data, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
}

void skyBox::draw(){
	glDepthMask(GL_FALSE);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, texture);

	glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, skyboxVAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 36);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDepthMask(GL_TRUE);
}


void skyBox::move(float x, float y, float z){
	for(int i = 0; i < 108; i++){
		if(i%3 == 0 )g_vertex_buffer_data[i]+=x;
		if(i%3 == 1 )g_vertex_buffer_data[i]+=y;
		if(i%3 == 2 )g_vertex_buffer_data[i]+=z;
	}
}
void skyBox::scale(float x, float y, float z){
	for(int i = 0; i < 108; i++){
		if(i%3 == 0 )g_vertex_buffer_data[i]*=x;
		if(i%3 == 1 )g_vertex_buffer_data[i]*=y;
		if(i%3 == 2 )g_vertex_buffer_data[i]*=z;
	}
}

void skyBox::cleanup(){
	glDeleteBuffers(1,&vertexbuffer);
	glDeleteBuffers(1,&uvbuffer);
}

