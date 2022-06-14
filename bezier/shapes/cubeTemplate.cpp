#include <iostream>
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <glad/glad.h>
using namespace glm;

#include "cubeTemplate.hpp"


cubeTemplate::cubeTemplate(GLuint shaderprogramID){
	this->programID = shaderprogramID;
}

void cubeTemplate::loadTexture(GLuint mytex){
	this->texture = mytex;
}

void cubeTemplate::loadTexture(char* src){
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
		std::cout << "Failed to load texture "<<src << std::endl;
	}
	stbi_image_free(data);
	this->texture = texture;
}

void cubeTemplate::prep(){
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	
	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &normal);
	glBindBuffer(GL_ARRAY_BUFFER, normal);
	glBufferData(GL_ARRAY_BUFFER, sizeof(normals), normals, GL_STATIC_DRAW);

	std::vector<float> tang;
	std::vector<float> btang;
	int ui = 0;
	vec3 tangent1;
	vec3 bitangent1;
	for(int i = 0; i < 108-8; i+=9){
		vec3 edge1 = vec3(g_vertex_buffer_data[i+3],g_vertex_buffer_data[i+4],g_vertex_buffer_data[i+5]) - vec3(g_vertex_buffer_data[i],g_vertex_buffer_data[i+1],g_vertex_buffer_data[i+2]);
		vec3 edge2 = vec3(g_vertex_buffer_data[i+6],g_vertex_buffer_data[i+7],g_vertex_buffer_data[i+8]) - vec3(g_vertex_buffer_data[i],g_vertex_buffer_data[i+1],g_vertex_buffer_data[i+2]);
		vec2 deltaUV1 = vec2(g_uv_buffer_data[ui+2],g_uv_buffer_data[ui+3]) - vec2(g_uv_buffer_data[ui],g_uv_buffer_data[ui+1]);
		vec2 deltaUV2 = vec2(g_uv_buffer_data[ui+4],g_uv_buffer_data[ui+5]) - vec2(g_uv_buffer_data[ui],g_uv_buffer_data[ui+1]);
		
		float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

		tangent1.x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
		tangent1.y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
		tangent1.z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
		tang.push_back(tangent1.x);
		tang.push_back(tangent1.y);
		tang.push_back(tangent1.z);
		bitangent1.x = f * (-deltaUV2.x * edge1.x + deltaUV1.x * edge2.x);
		bitangent1.y = f * (-deltaUV2.x * edge1.y + deltaUV1.x * edge2.y);
		bitangent1.z = f * (-deltaUV2.x * edge1.z + deltaUV1.x * edge2.z);
		btang.push_back(bitangent1.x);
		btang.push_back(bitangent1.y);
		btang.push_back(bitangent1.z);
		ui+=6;
	}

	glGenBuffers(1, &tangent);
	glBindBuffer(GL_ARRAY_BUFFER, tangent);
	glBufferData(GL_ARRAY_BUFFER, tang.size() * sizeof(glm::vec3), &tang[0], GL_STATIC_DRAW);

	glGenBuffers(1, &bitangent);
	glBindBuffer(GL_ARRAY_BUFFER, bitangent);
	glBufferData(GL_ARRAY_BUFFER, tang.size() * sizeof(glm::vec3), &btang[0], GL_STATIC_DRAW);
	
}


void cubeTemplate::draw(){
	//prog.use();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, cubeTemplate::vertexbuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cubeTemplate::uvbuffer);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

void cubeTemplate::move(float x, float y, float z){
	for(int i = 0; i < 108; i++){
		if(i%3 == 0 )g_vertex_buffer_data[i]+=x;
		if(i%3 == 1 )g_vertex_buffer_data[i]+=y;
		if(i%3 == 2 )g_vertex_buffer_data[i]+=z;
	}
}
void cubeTemplate::scale(float x, float y, float z){
	for(int i = 0; i < 108; i++){
		if(i%3 == 0 )g_vertex_buffer_data[i]*=x;
		if(i%3 == 1 )g_vertex_buffer_data[i]*=y;
		if(i%3 == 2 )g_vertex_buffer_data[i]*=z;
	}
}

void cubeTemplate::read(){
	for(int i = 2; i < 108; i+=3){
		std::cout<<"X: "<<g_vertex_buffer_data[i-2]<<"  Y:  "<<g_vertex_buffer_data[i-1]<<"  Z  "<<g_vertex_buffer_data[i]<<"\n";
	}
}
void cubeTemplate::cleanup(){
	glDeleteBuffers(1,&vertexbuffer);
	glDeleteBuffers(1,&uvbuffer);
}


void cubeTemplate::drawNormal(){
	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseMap);
    

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, cubeTemplate::vertexbuffer);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	// 2nd attribute buffer : UVs
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cubeTemplate::uvbuffer);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,(void*)0);

	glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, normalMap);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, cubeTemplate::normal);
	glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	glEnableVertexAttribArray(3);
	glBindBuffer(GL_ARRAY_BUFFER, cubeTemplate::tangent);
	glVertexAttribPointer(3,3,GL_FLOAT,GL_FALSE,0,(void*)0);

	glEnableVertexAttribArray(4);
	glBindBuffer(GL_ARRAY_BUFFER, cubeTemplate::bitangent);
	glVertexAttribPointer(4,3,GL_FLOAT,GL_FALSE,0,(void*)0);

    glDrawArrays(GL_TRIANGLES, 0, 12*3);

    glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}
void cubeTemplate::setNormal(unsigned int dMap, unsigned int nMap){
	diffuseMap = dMap;
    normalMap = nMap;
}