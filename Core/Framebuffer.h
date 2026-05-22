// pup3D - puppy powered engine
// Framebuffer.h
// Defines an opengl framebuffer and associated mesh for rendering as a screenspace quad
// Skye Whelan

#pragma once
#include <glew.h>
#include <glfw3.h>

class Framebuffer
{
private:
    GLuint m_MultisampleFBO = 0;
    GLuint m_IntermediateFBO = 0;
    GLuint m_Color = 0;
    GLuint m_ResolvedColor = 0;
    GLuint m_Depth = 0;
    GLuint m_VBO = 0;
    GLuint m_EBO = 0;
    GLuint m_VAO = 0;
    GLuint m_ShaderProgram = 0;
public:
    Framebuffer();
    
    void Render();
    void Regenerate();
    
    GLuint GetMultisampleFBO();
    GLuint GetIntermediateFBO();
    GLuint GetColor();
    GLuint GetDepth();
};
