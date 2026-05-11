// pup3D - puppy powered engine
// Mesh.cpp
// 
// Skye Whelan

#include "Mesh.h"

Mesh::Mesh(MeshData _shape)
{
    m_IndexCount = _shape.Indices.size();
    
    // Create Vertex Array Object
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    // Create Vertex Buffer Object
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * _shape.Vertices.size(), _shape.Vertices.data(), GL_STATIC_DRAW);
    
    // Create Element Buffer Object
    glGenBuffers(1, &m_EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * m_IndexCount, _shape.Indices.data(), GL_STATIC_DRAW);
    
    // Set vertex attribute pointers
    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
    glEnableVertexAttribArray(0); 
    // TexCoords
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);
    
    //
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

Mesh::~Mesh()
{
}

void Mesh::Render()
{
    // Bind VAO
    glBindVertexArray(m_VAO);
    
    // Draw
    glDrawElements(GL_TRIANGLES, m_IndexCount, GL_UNSIGNED_INT, 0);
    
    // Unbind VAO
    glBindVertexArray(0);
}
