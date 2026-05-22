#version 460 core

layout (location = 0) in vec3 inVertexPos;
layout (location = 1) in vec2 inTexCoords;
layout (location = 2) in vec3 inVertexNormal;

uniform mat4 PVM;
uniform mat4 Model;
uniform float MinHeight;
uniform float MaxHeight;

out vec2 TexCoords;
out vec3 FragPosition;
out vec3 FragNormal;
out float NormalisedHeight;

void main()
{
    gl_Position = PVM * vec4(inVertexPos, 1.0f);
    TexCoords = inTexCoords;
    FragNormal = mat3(transpose(inverse(Model))) * inVertexNormal;
    FragPosition = vec3(Model * vec4(inVertexPos, 1.0f));
    
    NormalisedHeight = (inVertexPos.y - MinHeight) / (MaxHeight - MinHeight);
    NormalisedHeight = 1 - pow(1 - NormalisedHeight, 2);
}