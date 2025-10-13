#version 330 core

in vec3 vertexColor; // from the vertex shader output
out vec4 FragColor; // final output color

uniform float uBrightness; // test a float uniform

void main()
{
    FragColor = vec4(vertexColor * uBrightness, 1.0);
}