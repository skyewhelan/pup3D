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
            // Position             // TexCoords
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, // Bottom Left
             0.5f, -0.5f, 0.0f,     1.0f, 0.0f, // Bottom Right
             0.0f,  0.5f, 0.0f,     0.5f, 1.0f  // Top Center
        };
        
        std::vector<GLuint> Indices = {
            0, 1, 2
        };
        
        return {Vertices, Indices};
    }
    
    static MeshData Quad()
    {
        std::vector<GLfloat> Vertices = {
            // Position             // TexCoords
            0.5f,  0.5f, 0.0f,      1.0f, 1.0f, // Top Right
            0.5f, -0.5f, 0.0f,      1.0f, 0.0f, // Bottom Right
           -0.5f, -0.5f, 0.0f,      0.0f, 0.0f, // Bottom Left
           -0.5f,  0.5f, 0.0f,      0.0f, 1.0f  // Top Left 
        };
        
        std::vector<GLuint> Indices = {
            0, 1, 3,   // first triangle
            1, 2, 3    // second triangle
        };
        
        return {Vertices, Indices};
    }
    
    static MeshData Cube()
    {
        std::vector<GLfloat> Vertices = { // Vertices for cube mesh
            // Position                // Texture Coords

            // Front Quad
            -0.5f, 0.5f, 0.5f,        0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,        0.0f, 0.0f,
            0.5f, -0.5f, 0.5f,        1.0f, 0.0f,
            0.5f, 0.5f, 0.5f,        1.0f, 1.0f,

            // Back Quad
            0.5f, 0.5f, -0.5f,        0.0f, 1.0f,
            0.5f, -0.5f, -0.5f,        0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
            -0.5f, 0.5f, -0.5f,        1.0f, 1.0f,

            // Right
            0.5f, 0.5f, 0.5f,        0.0f, 1.0f,
            0.5f, -0.5f, 0.5f,        0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,        1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,        1.0f, 1.0f,

            // Left
            -0.5f, 0.5f, -0.5f,        0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,        1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,        1.0f, 1.0f,

            // Top
            -0.5f, 0.5f, -0.5f,        0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,        0.0f, 0.0f,
            0.5f, 0.5f, 0.5f,        1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,        1.0f, 1.0f,

            // Bottom
            -0.5f, -0.5f, 0.5f,        0.0f, 1.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,        1.0f, 0.0f,
            0.5f, -0.5f, 0.5f,        1.0f, 1.0f,
        };

        std::vector<GLuint> Indices = { // Indices for cube mesh
            0, 1, 2,
            0, 2, 3,
            4, 5, 6,
            4, 6, 7,
            8, 9, 10,
            8, 10, 11,
            12, 13, 14,
            12, 14, 15,
            16, 17, 18,
            16, 18, 19,
            20, 21, 22,
            20, 22, 23,
        };
        
        return {Vertices, Indices};
    }
}