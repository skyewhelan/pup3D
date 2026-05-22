#version 460 core

struct MaterialData
{
    sampler2D Texture;
};

in vec2 TexCoords;
in vec3 FragPosition;
in vec3 FragNormal;

out vec4 FragColor;

uniform MaterialData Material;

void main()
{
    // Correct TexCoords will display on a quad as follows:
    // Top left: blue
    // Top right: purple
    // Bottom left: black
    // Bottom right: red

    FragColor = texture(Material.Texture, TexCoords) * vec4(1 - FragNormal.x, 1 - FragNormal.y, 1 - FragNormal.z, 1.0f);
}