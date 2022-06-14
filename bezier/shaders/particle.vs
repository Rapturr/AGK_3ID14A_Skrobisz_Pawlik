#version 400 core

in vec3 VertexPosition;
//layout (location = 0 ) in vec3 VertexPosition;


uniform mat4 MVP;
uniform vec3 Position;
uniform mat4 u_Transform;
void main()
{
    gl_Position = MVP * vec4(VertexPosition+Position, 1.0);
}