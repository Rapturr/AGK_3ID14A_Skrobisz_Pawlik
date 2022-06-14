#version 400

layout (location = 0 ) in vec3 VertexPosition;
layout(location = 1) in vec2 vertexUV;

out vec2 UV;

uniform vec3 positionOffset;
uniform bool susan;
void main()
{
    //gl_Position = vec4(VertexPosition, 1.0);
    //if(susan){
        gl_Position = vec4(VertexPosition, 1.0);
        UV = vertexUV;
    //}
    //gl_Position *= positionOffset;
}