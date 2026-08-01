// pup3D - puppy powered engine
// Terrain.cpp
// 
// Skye Whelan

#include "Terrain.h"

#include <glew.h>
#include <glfw3.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <filesystem>
#include "../../Assets/Shader.h"
#include "../../Core/RenderSettings.h"
#include "../../Assets/TextureAsset.h"
#include "../Components/Cameras/Camera.h"
#include "../../Assets/Material.h"

Terrain::Terrain(std::string _heightmap, Material* _material)
{
    m_Material = _material;
    LoadHeightmap(_heightmap, _material);
}

Terrain::Terrain(std::string _heightmap, Material* _material, float _spacing, float _heightScale, float _yOffset)
{
    m_Spacing = _spacing;
    m_HeightScale = _heightScale;
    m_VertexOffset.y = _yOffset;
    m_Material = _material;
    LoadHeightmap(_heightmap, _material);
}

void Terrain::LoadHeightmap(std::string _fileName, Material* _material)
{
    auto size = std::filesystem::file_size("Resources/HeightMaps/" + _fileName);
    m_VertexCount = size / sizeof(float);
    std::cout << m_VertexCount << " " << size << "\n";
    
    std::vector<float> HeightMap(m_VertexCount);
    
    // Open the file.
    std::ifstream File;
    File.open(("Resources/HeightMaps/" + _fileName).c_str(), std::ios_base::binary);
    if (File)
    {
        File.read((char*)HeightMap.data(), m_VertexCount * sizeof(float));
        File.close();
    }
    
    // Squirt (sqrt) is the number of rows or columns
    unsigned int Squirt = sqrt(m_VertexCount);
    
    // Offset to center the mesh on the terrain position
    m_VertexOffset.x = (-(float)Squirt * m_Spacing) / 2.0f;
    m_VertexOffset.z = (-(float)Squirt * m_Spacing) / 2.0f;
    
    // Find lowest and highest final heights for use in shaders
    auto Minmax = std::ranges::minmax(HeightMap);
    m_MinHeight = (Minmax.min * m_HeightScale) + m_VertexOffset.y;
    m_MaxHeight = (Minmax.max * m_HeightScale) + m_VertexOffset.y;
    
    // Vertex Data
    std::vector<GLfloat> Vertices;
    // Index Data
    std::vector<GLuint> Indices;
    
    for (unsigned int Row = 0; Row < Squirt; Row++)
    {   
        for (unsigned int Col = 0; Col < Squirt; Col++)
        {
            // Position
            Vertices.push_back(((GLfloat)Col * m_Spacing) + m_VertexOffset.x);                           // Pos X
            Vertices.push_back((HeightMap[(Row * Squirt) + Col] * m_HeightScale) + m_VertexOffset.y);    // Pos Y
            Vertices.push_back(((GLfloat)Row * m_Spacing) + m_VertexOffset.z);                           // Pos Z
            
            // Tex Coords
            Vertices.push_back((GLfloat)Col / (GLfloat)Squirt); // Tex X
            Vertices.push_back((GLfloat)Row / (GLfloat)Squirt); // Tex Y      
            
            // Normals - calculated at a later step but space must be allocated here
            Vertices.push_back(0.0f);   // Normal X
            Vertices.push_back(0.0f);   // Normal Y
            Vertices.push_back(0.0f);   // Normal Z
            
            // Indices
            if (Row < Squirt - 1 && Col < Squirt - 1)
            {
                Indices.push_back((Row * Squirt) + Col);            // Top left
                Indices.push_back(((Row + 1) * Squirt) + Col);      // Bottom left
                Indices.push_back((Row * Squirt) + Col + 1);        // Top right

                Indices.push_back((Row * Squirt) + Col + 1);        // Top right
                Indices.push_back(((Row + 1) * Squirt) + Col);      // Bottom left
                Indices.push_back(((Row + 1) * Squirt) + Col + 1);  // Bottom right
            }
        }
    }
    
    
    // Normals need their own loop
    
    unsigned int Stride = 5;
    for (unsigned int Row = 0; Row < Squirt; Row++)
    {
        for (unsigned int Col = 0; Col < Squirt; Col++)
        {
            // Clamp to ensure we cannot access vertices out of range
            unsigned int PrevRow = std::max(0, (int)Row - 1);
            unsigned int NextRow = std::min(Squirt - 1, Row + 1);
            unsigned int PrevCol = std::max(0, (int)Col - 1);
            unsigned int NextCol = std::min(Squirt - 1, Col + 1);
            
            // Find surrounding vertices
            float Up = HeightMap[(PrevRow * Squirt) + Col] * m_HeightScale;
            float Down = HeightMap[(NextRow * Squirt) + Col] * m_HeightScale;
            float Left = HeightMap[(Row * Squirt) + PrevCol] * m_HeightScale;
            float Right = HeightMap[(Row * Squirt) + NextCol] * m_HeightScale;
            
            float dx = (Right - Left) / (2.0f * m_Spacing);
            float dz = (Up - Down) / (2.0f * m_Spacing);
            glm::vec3 Normal = glm::normalize(glm::vec3(dx, 1.0, dz));
            
            Vertices[(Row * Squirt) + Col + Stride] = Normal.x;
            Vertices[(Row * Squirt) + Col + Stride + 1] = Normal.y;
            Vertices[(Row * Squirt) + Col + Stride + 2] = Normal.z;
            Stride += 7;
        }
    }
    
    m_IndexCount = (GLuint)Indices.size();
    
    
    // Create Vertex Array Object
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    // Create Vertex Buffer Object
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * Vertices.size(), Vertices.data(), GL_STATIC_DRAW);
    
    // Create Element Buffer Object
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * Indices.size(), Indices.data(), GL_STATIC_DRAW);
    
    // Set vertex attribute pointers
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0); 
    // TexCoords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    // Normals
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);
    
    glPointSize(5.0f);
}

void Terrain::Update(float _terrain)
{
    // Reset to identity
    m_Model = glm::mat4(1.0f);
    
    // Scale should be set via m_Spacing (XZ) and m_HeightScale (Y)
    
    // Rotate
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.x), { 1.0f, 0.0f, 0.0f });
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.y), { 0.0f, 1.0f, 0.0f });
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.z), { 0.0f, 0.0f, 1.0f });
    // Translate
    m_Model = glm::translate(m_Model, m_Position);
}

void Terrain::Render()
{
    glUseProgram(m_Material->GetShaderProgram());
    
    if (m_Material->GetTexture())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Material->GetTexture()->GetID());
    }
    
    Camera* Cam = RS::GetRenderCamera();
    Shader::UniformMat4(m_Material->GetShaderProgram(), "PVM", Cam->GetProjection() * Cam->GetView() * m_Model);
    Shader::UniformMat4(m_Material->GetShaderProgram(), "Model", m_Model);
    m_Material->SetUniforms();
    //Shader::UniformVec4(m_ShaderProgram, "Material.Albedo", {1.5f, 1.5f, 1.5f, 1.0f});
    //Shader::UniformI(m_ShaderProgram, "Material.Texture", 0);
    //Shader::UniformF(m_ShaderProgram, "Tiling", 50.0f);
    //Shader::UniformF(m_ShaderProgram, "MinHeight", m_MinHeight);
    //Shader::UniformF(m_ShaderProgram, "MaxHeight", m_MaxHeight);
    
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glUseProgram(0);
}

void Terrain::SetPosition(glm::vec3 _position)
{
    m_Position = _position;
}

void Terrain::SetRotation(glm::vec3 _rotation)
{
    m_Rotation = _rotation;
}
