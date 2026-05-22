#pragma once
#include <glew.h>
#include <string>
#include <vec3.hpp>
#include <vector>

class TextureAsset;

class Terrain
{
    // Space between each vertex on the X and Z axes
    float m_Spacing = 0.75f;
    // Scalar for heightmap values
    float m_HeightScale = 0.1f;
    // Offset to apply when loading vertices; X and Z generated in LoadHeightmap()
    glm::vec3 m_Offset = { 0.0f, -10.0f, 0.0f };
    // Smallest value in heightmap
    float m_MinHeight;
    // Largest value in heightmap
    float m_MaxHeight;
    // Number of vertices
    GLuint m_VertexCount;
    // Number of indices
    GLuint m_IndexCount;
    
    GLuint m_VBO;
    GLuint m_EBO;
    GLuint m_VAO;
    GLuint m_ShaderProgram;
    TextureAsset* m_Texture;
public:
    Terrain();
    Terrain(std::string _heightmap, float _spacing, float _heightScale, float _yOffset);
    
    // Generate terrain mesh from heightmap
    void LoadHeightmap(std::string _fileName);
    
    // Render terrain mesh; runs every frame
    void Render();
};
