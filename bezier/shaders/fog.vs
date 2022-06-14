#version 400 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec2 vertexUV;

out vec3 modelPos;
out vec2 UV;

uniform mat4 MVP;
uniform vec3 pos;
void main()
{
    gl_Position = MVP * vec4(vertexPosition+pos, 1.0);
    UV = vertexUV;
    modelPos = vertexPosition + pos;
}