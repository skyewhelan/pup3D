// pup3D - puppy powered engine
// Skybox.cpp
// 
// Skye Whelan

#include "Skybox.h"

#include <glew.h>
#include <stb_image.h>
#include <vector>
#include <gtc/type_ptr.hpp>
#include "../Assets/Shader.h"
#include "../Core/RenderSettings.h"
#include "../Resources/Shape.h"
#include "Components/Cameras/Camera.h"

Skybox::Skybox(std::string _cubemapPath)
{
    int Width;
    int Height;
    int Channels;
    glGenTextures(1, &m_Cubemap);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Cubemap);
    
    stbi_set_flip_vertically_on_load(false);
    unsigned char*  Data = stbi_load((_cubemapPath + "right.png").c_str(), &Width, &Height, &Channels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    
    Data = stbi_load((_cubemapPath + "left.png").c_str(), &Width, &Height, &Channels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    
    Data = stbi_load((_cubemapPath + "top.png").c_str(), &Width, &Height, &Channels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    
    Data = stbi_load((_cubemapPath + "bottom.png").c_str(), &Width, &Height, &Channels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    
    Data = stbi_load((_cubemapPath + "front.png").c_str(), &Width, &Height, &Channels, 0);
    glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    
    Data = stbi_load((_cubemapPath + "back.png").c_str(), &Width, &Height, &Channels, 0); 
    glTexImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
    
    stbi_set_flip_vertically_on_load(true);
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    
    std::vector<GLfloat> Vertices = Shape::Skybox();
    
    // Create Vertex Array Object
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    // Create Vertex Buffer Object
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
    
    // Set vertex attribute pointers
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0);
    
    m_ShaderProgram = Shader::CreateProgram({
        Shader::Compile("Resources/Shaders/Skybox.vert", GL_VERTEX_SHADER),
        Shader::Compile("Resources/Shaders/Skybox.frag", GL_FRAGMENT_SHADER)
    });
}

void Skybox::Render()
{
    Camera* Cam = RS::GetRenderCamera();
    glm::mat4 View = glm::mat4(glm::mat3(Cam->GetView()));
    glm::mat4 Projection = Cam->GetProjection();
    
    glDepthFunc(GL_LEQUAL);
    // ... set view and projection matrix
    glBindVertexArray(m_VAO);
    glUseProgram(m_ShaderProgram);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Cubemap);
    
    glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, "View"), 1, GL_FALSE, glm::value_ptr(View));
    glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, "Projection"), 1, GL_FALSE, glm::value_ptr(Projection));
    glUniform1i(glGetUniformLocation(m_ShaderProgram, "Cubemap"), 0);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
    glDepthFunc(GL_LESS);
    glBindVertexArray(0);
}
