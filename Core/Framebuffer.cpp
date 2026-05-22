// pup3D - puppy powered engine
// Framebuffer.cpp
// 
// Skye Whelan

#include "Framebuffer.h"
#include "../../Resources/Shape.h"

#include <iostream>

#include "../Assets/Shader.h"
#include "RenderSettings.h"

Framebuffer::Framebuffer()
{
    glm::ivec2 Size = RS::GetRenderResolution();
    GLint Filter = RS::GetRenderTextureFilter();
    int Samples = RS::GetSamples();
    
    glGenFramebuffers(1, &m_MultisampleFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_MultisampleFBO);
    
    glGenTextures(1, &m_Color);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_Color);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, Samples, GL_RGB, Size.x, Size.y, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, Filter);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, Filter);  
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_Color, 0);
    
    glGenTextures(1, &m_Depth);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_Depth);
    glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, Samples, GL_DEPTH_COMPONENT, Size.x, Size.y, GL_TRUE);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, Filter);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, Filter);  
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D_MULTISAMPLE, m_Depth, 0);
    
    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Multisample Framebuffer is incomplete" << "\n";
    }
    
    MeshData Quad = Shape::Quad();
    
    // Create Vertex Array Object
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    // Create Vertex Buffer Object
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Quad.Vertices.size(), Quad.Vertices.data(), GL_STATIC_DRAW);
    
    // Create Element Buffer Object
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * 6, Quad.Indices.data(), GL_STATIC_DRAW);
    
    // Set vertex attribute pointers
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0); 
    // TexCoords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    // Shaders
    GLuint Vert = Shader::Compile("Resources/Shaders/RenderTexture.vert", GL_VERTEX_SHADER);
    GLuint Frag = Shader::Compile("Resources/Shaders/RenderTexture.frag", GL_FRAGMENT_SHADER);
    m_ShaderProgram = Shader::CreateProgram({Vert, Frag});
    
    // Intermediate Framebuffer
    glGenFramebuffers(1, &m_IntermediateFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, m_IntermediateFBO);
    
    glGenTextures(1, &m_ResolvedColor);
    glBindTexture(GL_TEXTURE_2D, m_ResolvedColor);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB, Size.x, Size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ResolvedColor, 0);	// we only need a color buffer

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
    {
        std::cout << "Intermediate Framebuffer is incomplete" << "\n";
    }
    
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Framebuffer::Render()
{
    glClearColor(0.0f, 1.0f, 0.0f, 1.0f); 
    glClear(GL_COLOR_BUFFER_BIT);
    
    
    glEnable(GL_FRAMEBUFFER_SRGB); 
    glDisable(GL_DEPTH_TEST);
    glUseProgram(m_ShaderProgram);
    glBindVertexArray(m_VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_ResolvedColor);
    
    Shader::UniformI(m_ShaderProgram, "RenderTexture", 0);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_FRAMEBUFFER_SRGB); 
    
}

void Framebuffer::Regenerate()
{
    glm::ivec2 Size = RS::GetRenderResolution();
    GLint Filter = RS::GetRenderTextureFilter();
    
    glDeleteTextures(1, &m_Color);
    glDeleteTextures(1, &m_Depth);
    
    glGenTextures(1, &m_Color);
    glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_Color);
    glTexImage2D(GL_TEXTURE_2D_MULTISAMPLE, 0, GL_RGB, Size.x, Size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, Filter);
    glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, Filter);  
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, m_Color, 0);
    
    glGenTextures(1, &m_Depth);
    glBindTexture(GL_TEXTURE_2D, m_Depth);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT, Size.x, Size.y, 0, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, Filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, Filter);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_Depth, 0);
}

GLuint Framebuffer::GetMultisampleFBO()
{
    return m_MultisampleFBO;
}

GLuint Framebuffer::GetIntermediateFBO()
{
    return m_IntermediateFBO;
}

GLuint Framebuffer::GetColor()
{
    return m_Color;
}

GLuint Framebuffer::GetDepth()
{
    return m_Depth;
}