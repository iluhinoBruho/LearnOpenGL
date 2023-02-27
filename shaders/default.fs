#version 330 core
out vec4 FragColor;
in vec3 ourColor;
//in vec3 ourPosition;

uniform float brightness;

void main()
{
    FragColor = vec4(ourColor, brightness);
}