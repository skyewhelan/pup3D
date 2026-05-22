// pup3D - puppy powered engine
// MeshAsset.h
// Defines a mesh to be used for rending actors in a scene
// Skye Whelan

#pragma once
#include "../Resources/Shape.h"

class MeshAsset
{
private:
    GLuint m_VBO; // Vertex Buffer Object; Stores vertices
    GLuint m_EBO; // Element Buffer Object; Stores indices
    GLuint m_VAO; // Vertex Array Object
    
    int m_IndexCount;
public:
    MeshAsset(MeshData _shape);
    ~MeshAsset();
    
    void Render();
};
