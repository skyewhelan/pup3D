#version 460 core

layout (location = 0) in vec3 inVertexPos;
layout (location = 1) in vec2 inTexCoords;

uniform mat4 PVM;

noperspective out vec2 TexCoords;

void main()
{
    gl_Position = PVM * vec4(inVertexPos, 1.0f);
    TexCoords = inTexCoords;
}