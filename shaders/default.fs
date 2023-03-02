#version 330 core
in vec3 ourColor;
in vec2 TexCoord;

out vec4 color;

uniform float brightness;
uniform sampler2D ourTexture1;
uniform sampler2D ourTexture2;

void main()
{
    //FragColor = vec4(ourColor, brightness);
    //color = texture(ourTexture, TexCoord)*vec4(ourColor, brightness);
    //color = vec4(ourColor, brightness) * mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(TexCoord.x, 1.0 - TexCoord.y)), 0.3);
    color = mix(texture(ourTexture1, TexCoord), texture(ourTexture2, vec2(TexCoord.x, 1.0 - TexCoord.y)), 0.15);
}