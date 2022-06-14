#version 400 core

//in vec3 VertexPosition;
layout (location = 0 ) in vec3 VertexPosition;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;
out vec3 vertexpos;

uniform mat4 MVP;
uniform vec3 Position;
uniform mat4 u_Transform;
uniform mat4 direction;


void main()
{
    gl_Position = direction * vec4(VertexPosition+Position, 1.0);
    
    UV = vertexUV;

    vertexpos = VertexPosition;
}