#version 460 core

struct MaterialData
{
    vec4 Albedo;
};

in vec2 TexCoords;
in vec3 FragPosition;
in vec3 FragNormal;
in float NormalisedHeight;

out vec4 FragColor;

uniform MaterialData Material;

void main()
{
    FragColor = Material.Albedo * NormalisedHeight;
}