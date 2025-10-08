#version 330 core
layout(location = 0) in vec3 aPos; // vertex position
layout(location = 1) in vec3 aColor; // vertex color

out vec3 vertexColor; // pass to fragment shader

uniform mat4 uTransform; // test your mat4 uniform

void main()
{
    gl_Position = uTransform * vec4(aPos, 1.0);
    vertexColor = aColor;
}