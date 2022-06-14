#version 400 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;
out vec3 modelPos;
out vec3 lightDirection;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
uniform vec3 pos;
uniform vec3 lightPos;
void main(){

	// Output position of the vertex, in clip space : MVP * position
	gl_Position =  MVP * vec4(vertexPosition_modelspace+pos,1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
	modelPos = vertexPosition_modelspace+pos;
	lightDirection = normalize(lightPos - gl_Position.xyz);
}

