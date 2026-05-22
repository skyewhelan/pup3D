#version 460 core

noperspective in vec2 TexCoords;

uniform sampler2D Texture;

out vec4 FragColor;

void main()
{
    FragColor = texture(Texture, TexCoords);
}