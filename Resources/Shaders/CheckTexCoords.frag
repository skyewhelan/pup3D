#version 460 core

in vec2 TexCoords;

uniform sampler2D Texture;

out vec4 FragColor;

void main()
{
    // Correct TexCoords will display on a quad as follows:
    // Top left: blue
    // Top right: purple
    // Bottom left: black
    // Bottom right: red
    
    FragColor = vec4(TexCoords.x, 0.0f, TexCoords.y, 1.0f);
}