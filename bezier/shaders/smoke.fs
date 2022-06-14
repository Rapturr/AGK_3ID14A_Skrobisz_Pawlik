#version 400 core

in vec2 UV;
in vec3 vertexpos;
//layout ( location = 0 ) out vec4 FragColor;
out vec4 color;

uniform vec2 center;
uniform vec4 Color;
uniform sampler2D myTextureSampler;
void main(){
    //color = vec4(Color.r,Color.g,Color.b,0.3f);

    color = texture( myTextureSampler, UV ).rgba;
    //color = vec4(0.3f,0.6f,0.7f,0.3f);
    color = Color;
    vec2 pos = vertexpos.xy;
    
    float dist = distance(pos, center);
    //dist = 1/ dist;
    /*if(dist <0)
        dist = -dist;*/
    color = color/dist;
    if(dist > 0.8)
        color.a = 0.0f;
}