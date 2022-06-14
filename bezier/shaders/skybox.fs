#version 400 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 modelPos;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform samplerCube myTextureSampler;
uniform float attenuation;
uniform int progowanie;
uniform vec3 lightDir;
uniform int oswietlenie;
uniform vec4 lightColor;
uniform bool sun;
uniform bool setcolor = false;

uniform bool skybox = false;
void main(){
	color = texture( myTextureSampler, modelPos);
}

