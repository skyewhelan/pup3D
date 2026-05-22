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

Terrain::Terrain()
{
}

Terrain::Terrain(std::string _heightmap, float _spacing, float _heightScale, float _yOffset)
{
    m_Spacing = _spacing;
    m_HeightScale = _heightScale;
    m_Offset.y = _yOffset;
    LoadHeightmap(_heightmap);
}

void Terrain::LoadHeightmap(std::string _fileName)
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
    
    // for (unsigned int i = 0; i < m_VertexCount; i++)
    // {
    //     std::cout << HeightMap[i] << " ";
    // }
    
    // Vertex Data
    std::vector<GLfloat> Vertices;
    
    // Squirt (sqrt) is the number of rows or columns
    unsigned int Squirt = sqrt(m_VertexCount);
    
    m_Offset.x = (-(float)Squirt * m_Spacing) / 2.0f;
    m_Offset.z = (-(float)Squirt * m_Spacing) / 2.0f;
    
    auto Minmax = std::ranges::minmax(HeightMap);
    m_MinHeight = (Minmax.min * m_HeightScale) + m_Offset.y;
    m_MaxHeight = (Minmax.max * m_HeightScale) + m_Offset.y;
    
    for (unsigned int Row = 0; Row < Squirt; Row++)
    {   
        for (unsigned int Col = 0; Col < Squirt; Col++)
        {
            // Position
            Vertices.push_back(((GLfloat)Col * m_Spacing) + m_Offset.x);                           // Pos X
            Vertices.push_back((HeightMap[(Row * Squirt) + Col] * m_HeightScale) + m_Offset.y);    // Pos Y
            Vertices.push_back(((GLfloat)Row * m_Spacing) + m_Offset.z);                           // Pos Z
            
            // Tex Coords
            Vertices.push_back((GLfloat)Col / (GLfloat)Squirt); // Tex X
            Vertices.push_back((GLfloat)Row / (GLfloat)Squirt); // Tex Y      
            
            // Normals
            Vertices.push_back(0.0f);   // Normal X
            Vertices.push_back(1.0f);   // Normal Y
            Vertices.push_back(0.0f);   // Normal Z
        }
    }
    
    std::vector<GLuint> Indices;
    
    for (unsigned int Row = 0; Row < Squirt - 1; Row++)
    {
        for (unsigned int Col = 0; Col < Squirt - 1; Col++)
        {
            Indices.push_back((Row * Squirt) + Col);            // Top left
            Indices.push_back(((Row + 1) * Squirt) + Col);      // Bottom left
            Indices.push_back((Row * Squirt) + Col + 1);        // Top right

            Indices.push_back((Row * Squirt) + Col + 1);        // Top right
            Indices.push_back(((Row + 1) * Squirt) + Col);      // Bottom left
            Indices.push_back(((Row + 1) * Squirt) + Col + 1);  // Bottom right
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
    
    m_Texture = new TextureAsset("Resources/Textures/ground.png");
    
    // Shaders
    m_ShaderProgram = Shader::CreateProgram({
        Shader::Compile("Resources/Shaders/Terrain.vert", GL_VERTEX_SHADER),
        Shader::Compile("Resources/Shaders/TerrainColor.frag", GL_FRAGMENT_SHADER)
    });
    
    glPointSize(5.0f);
}

void Terrain::Render()
{
    glUseProgram(m_ShaderProgram);
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture->GetID());
    
    Camera* Cam = RS::GetRenderCamera();
    Shader::UniformMat4(m_ShaderProgram, "PVM", Cam->GetProjection() * Cam->GetView() * glm::mat4(1.0f));
    Shader::UniformMat4(m_ShaderProgram, "Model", glm::mat4(1.0f));
    Shader::UniformVec4(m_ShaderProgram, "Material.Albedo", {1.0f, 1.0f, 1.0f, 1.0f});
    //Shader::UniformI(m_ShaderProgram, "Material.Texture", 0);
    //Shader::UniformF(m_ShaderProgram, "Tiling", 100.0f);
    Shader::UniformF(m_ShaderProgram, "MinHeight", m_MinHeight);
    Shader::UniformF(m_ShaderProgram, "MaxHeight", m_MaxHeight);
    
    glBindVertexArray(m_VAO);
    //glDrawArrays(GL_POINTS, 0, m_VertexCount);
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
    
    glBindVertexArray(0);
    glUseProgram(0);
}
