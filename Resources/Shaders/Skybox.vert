#version 460 core
layout (location = 0) in vec3 VertexPosition;

out vec3 TexCoords;

uniform mat4 Projection;
uniform mat4 View;

void main()
{
    TexCoords = VertexPosition;
    gl_Position = vec4(Projection * View * vec4(VertexPosition, 1.0)).xyww;
}  