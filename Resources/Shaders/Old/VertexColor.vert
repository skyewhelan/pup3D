#version 460 core

layout (location = 0) in vec3 VertexPos;

out vec4 VertexColor;

void main()
{
    gl_Position = vec4(VertexPos.x, VertexPos.y, VertexPos.z, 1.0);
    
}