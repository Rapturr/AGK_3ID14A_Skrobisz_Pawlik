#version 400 core


uniform vec4 Color;
//layout ( location = 0 ) out vec4 FragColor;
out vec4 color;

void main()
{
    color = Color;
    color = vec4(1.0f,1.0f,1.0f,0.3f);
}