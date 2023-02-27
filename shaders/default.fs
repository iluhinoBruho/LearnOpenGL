#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform float brightness;
uniform sampler2D ourTexture;

void main()
{
    //FragColor = vec4(ourColor, brightness);
    color = texture(ourTexture, TexCoord)*vec4(ourColor, brightness);
}