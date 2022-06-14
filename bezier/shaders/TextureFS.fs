#version 400 core

// Interpolated values from the vertex shaders
in vec2 UV;
in vec3 modelPos;

// Ouput data
out vec4 color;

// Values that stay constant for the whole mesh.
uniform sampler2D myTextureSampler;
uniform float attenuation;
uniform int progowanie;
uniform vec3 lightDir;
uniform int oswietlenie;
uniform vec4 lightColor;
uniform bool sun;
uniform bool setcolor = false;
void main(){

	// Output color = color of the texture at the specified UV
	if(setcolor){
		color = vec4(0.3,0.5,0.7,1.0);
	}
	else{
		color = texture( myTextureSampler, UV ).rgba;
	}
	//color = vec4(color.r,color.g,color.b,color.a);
	
	if(attenuation != 0.0f)
		color = vec4(color.r*attenuation, color.g*attenuation, color.b*attenuation, color.a);
	if(progowanie == 1){
		float grey = color.r+color.g+color.b;
		grey /= 3;
		if(grey < 0.7)
			grey = 0.0f;
		else
			grey = 1.0f;
		color = vec4(grey,grey,grey, color.a);
	}
	if(progowanie == 2){
		float threshold = 0.5f;
		if(color.r < threshold)
			color.r = 0.0f;
		else
			color.r = 1.0f;
		if(color.g < threshold)
			color.g = 0.0f;
		else
			color.g = 1.0f;
		if(color.b < threshold)
			color.b = 0.0f;
		else
			color.b = 1.0f;
	}
}