// pup3D - puppy powered engine
// Terrain.h
// Defines a terrain actor with a mesh generated from a heightmap
// Skye Whelan

#pragma once
#include <glew.h>
#include <string>
#include <glm.hpp>
#include <vector>

class Material;
class TextureAsset;

class Terrain
{
    // Space between each vertex on the X and Z axes
    float m_Spacing = 0.75f;
    // Scalar for heightmap values
    float m_HeightScale = 0.35f;
    // Offset to apply when loading vertices; X and Z generated in LoadHeightmap(). Mesh will end up centered.
    glm::vec3 m_VertexOffset = { 0.0f, -10.0f, 0.0f };
    // Terrain's position in world space
    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    // Terrain's rotation in world space
    glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
    // Model matrix
    glm::mat4 m_Model = glm::mat4(1.0f);
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
    Material* m_Material = nullptr;
public:
    Terrain(std::string _heightmap, Material* _material);
    Terrain(std::string _heightmap, Material* _material, float _spacing, float _heightScale, float _yOffset);
    
    // Generate terrain mesh from heightmap
    void LoadHeightmap(std::string _fileName, Material* _material);
    
    //
    void Update(float _deltaTime);
    
    // Render terrain mesh; runs every frame
    void Render();
    
    void SetPosition(glm::vec3 _position);
    void SetRotation(glm::vec3 _rotation);
};
