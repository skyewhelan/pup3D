// pup3D - puppy powered engine
// Shape.h
// Defines vertices and indices of various primitive shapes
// Skye Whelan

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <vector>

struct MeshData
{
    std::vector<GLfloat> Vertices;
    std::vector<GLuint> Indices;
    
    MeshData(std::vector<GLfloat> _vertices, std::vector<GLuint> _indices)
    {
        Vertices = _vertices;
        Indices = _indices;
    }
};

namespace Shape
{
    static MeshData Triangle()
    {
        std::vector<GLfloat> Vertices = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f,  0.5f, 0.0f
        };
        
        std::vector<GLuint> Indices = {
            0, 1, 2
        };
        
        return {Vertices, Indices};
    }
    
    static MeshData Quad()
    {
        std::vector<GLfloat> Vertices = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
           -0.5f, -0.5f, 0.0f,  // bottom left
           -0.5f,  0.5f, 0.0f   // top left 
        };
        
        std::vector<GLuint> Indices = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        
        return {Vertices, Indices};
    }
}