#version 400 core

// Interpolated values from the vertex shaders
in vec2 UV;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform float attenuation;
void main(){

	// Output color = color of the texture at the specified UV
	color = texture( myTextureSampler, UV ).rgba;
	
	color = vec4(color.r*attenuation, color.g*attenuation, color.b*attenuation, color.a);

}