#version 460 core

struct MaterialData
{
    sampler2D Texture;
    vec4 Albedo;
};

in vec2 TexCoords;
in vec3 FragPosition;
in vec3 FragNormal;

out vec4 FragColor;

uniform MaterialData Material;
uniform float Tiling = 1.0f;

void main()
{
    FragColor = Material.Albedo * texture(Material.Texture, TexCoords * Tiling);
}