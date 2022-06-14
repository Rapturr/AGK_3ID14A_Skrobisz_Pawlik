#version 400

layout ( location = 0 ) out vec4 FragColor;
in vec2 UV;
uniform vec4 LineColor;
uniform sampler2D myTextureSampler;
uniform bool susan;
void main()
{
    FragColor = LineColor;
    //color = vec4(1.0,1.0,1.0,1.0);
}