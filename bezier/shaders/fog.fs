#version 400 core

// Interpolated values from the vertex shaders

in vec3 modelPos;
in vec2 UV;
// Wynikowy kolor piksela (fragmentu):
out vec4 color;

uniform vec3 camerapos;
uniform vec4 FogColor;
uniform sampler2D myTextureSampler;

float getFogFactor(float d)
{
    const float FogMax = 20.0;
    const float FogMin = 10.0;

    if (d>=FogMax) return 1;
    if (d<=FogMin) return 0;

    return 1 - (FogMax - d) / (FogMax - FogMin);
}
void main(){
    color = texture( myTextureSampler, UV ).rgba;
    // Współczynnik gęstości mgły:
    float d = distance(camerapos, modelPos);
    float alpha = getFogFactor(d);

    color = mix(color, FogColor, alpha);
}