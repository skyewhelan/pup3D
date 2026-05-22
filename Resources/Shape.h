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
            -0.5f, -0.5f, 0.0f,     0.0f, 0.0f,       0.0f, 0.0f, -1.0f, // Bottom Left
             0.5f, -0.5f, 0.0f,     1.0f, 0.0f,       0.0f, 0.0f, -1.0f, // Bottom Right
             0.0f,  0.5f, 0.0f,     0.5f, 1.0f,       0.0f, 0.0f, -1.0f,  // Top Center
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
        	-0.5f, 0.5f, 0.0,        0.0f, 1.0f,       0.0f, 0.0f, 1.0f,
			-0.5f, -0.5f, 0.0f,        0.0f, 0.0f,       0.0f, 0.0f, 1.0f,
			0.5f, -0.5f, 0.0f,        1.0f, 0.0f,       0.0f, 0.0f, 1.0f,
			0.5f, 0.5f, 0.0f,        1.0f, 1.0f,       0.0f, 0.0f, 1.0f,
        };
        
        std::vector<GLuint> Indices = {
            0, 1, 2,   // first triangle
            0, 2, 3    // second triangle
        };
        
        return {Vertices, Indices};
    }
    
    static MeshData DoubleQuad()
    {
        std::vector<GLfloat> Vertices = {
            // Position             // TexCoords
            0.5f,  0.5f, 0.0f,      1.0f, 1.0f,       0.0f, 0.0f, -1.0f, // Top Right
            0.5f, -0.5f, 0.0f,      1.0f, 0.0f,       0.0f, 0.0f, -1.0f, // Bottom Right
           -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,       0.0f, 0.0f, -1.0f, // Bottom Left
           -0.5f,  0.5f, 0.0f,      0.0f, 1.0f,       0.0f, 0.0f, -1.0f, // Top Left
            
            // Position             // TexCoords
            0.5f,  0.5f, 0.0f,      1.0f, 1.0f,       0.0f, 0.0f, 1.0f, // Top Right
            0.5f, -0.5f, 0.0f,      1.0f, 0.0f,       0.0f, 0.0f, 1.0f, // Bottom Right
           -0.5f, -0.5f, 0.0f,      0.0f, 0.0f,       0.0f, 0.0f, 1.0f, // Bottom Left
           -0.5f,  0.5f, 0.0f,      0.0f, 1.0f,       0.0f, 0.0f, 1.0f, // Top Left 
        };
        
        std::vector<GLuint> Indices = {
            0, 1, 3,    // First triangle
            1, 2, 3,    // Second triangle
            7, 5, 4,    // 
            7, 6, 5,    //
        };
        
        return {Vertices, Indices};
    }
    
    static MeshData Cube()
    {
        std::vector<GLfloat> Vertices = { // Vertices for cube mesh
            // Position                // Texture Coords    // Normals

            // Front Quad
            -0.5f, 0.5f, 0.5f,        0.0f, 1.0f,       0.0f, 0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,        0.0f, 0.0f,       0.0f, 0.0f, 1.0f,
            0.5f, -0.5f, 0.5f,        1.0f, 0.0f,       0.0f, 0.0f, 1.0f,
            0.5f, 0.5f, 0.5f,        1.0f, 1.0f,       0.0f, 0.0f, 1.0f,

            // Back Quad
            0.5f, 0.5f, -0.5f,        0.0f, 1.0f,       0.0f, 0.0f, -1.0f,
            0.5f, -0.5f, -0.5f,        0.0f, 0.0f,       0.0f, 0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,    1.0f, 0.0f,       0.0f, 0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f,        1.0f, 1.0f,       0.0f, 0.0f, -1.0f,

            // Right
            0.5f, 0.5f, 0.5f,        0.0f, 1.0f,       1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, 0.5f,        0.0f, 0.0f,       1.0f, 0.0f, 0.0f,
            0.5f, -0.5f, -0.5f,        1.0f, 0.0f,       1.0f, 0.0f, 0.0f,
            0.5f, 0.5f, -0.5f,        1.0f, 1.0f,       1.0f, 0.0f, 0.0f,

            // Left
            -0.5f, 0.5f, -0.5f,        0.0f, 1.0f,       -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,       -1.0f, 0.0f, 0.0f,
            -0.5f, -0.5f, 0.5f,        1.0f, 0.0f,       -1.0f, 0.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,        1.0f, 1.0f,       -1.0f, 0.0f, 0.0f,

            // Top
            -0.5f, 0.5f, -0.5f,        0.0f, 1.0f,       0.0f, 1.0f, 0.0f,
            -0.5f, 0.5f, 0.5f,        0.0f, 0.0f,       0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, 0.5f,        1.0f, 0.0f,       0.0f, 1.0f, 0.0f,
            0.5f, 0.5f, -0.5f,        1.0f, 1.0f,       0.0f, 1.0f, 0.0f,

            // Bottom
            -0.5f, -0.5f, 0.5f,        0.0f, 1.0f,       0.0f, -1.0f, 0.0f,
            -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,       0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, -0.5f,        1.0f, 0.0f,       0.0f, -1.0f, 0.0f,
            0.5f, -0.5f, 0.5f,        1.0f, 1.0f,       0.0f, -1.0f, 0.0f,
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
    
    static std::vector<GLfloat> Skybox()
    {
        return {
            -1.0f,  1.0f, -1.0f,
           -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f, -1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

           -1.0f, -1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f, -1.0f,  1.0f,
           -1.0f, -1.0f,  1.0f,

           -1.0f,  1.0f, -1.0f,
            1.0f,  1.0f, -1.0f,
            1.0f,  1.0f,  1.0f,
            1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f,  1.0f,
           -1.0f,  1.0f, -1.0f,

           -1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
           -1.0f, -1.0f,  1.0f,
            1.0f, -1.0f,  1.0f
        };
    }
    
    static MeshData Sphere(float _radius, int _fidelity)
	{
		int VertexAttrib = 8;	// Float components are needed for each vertex point
		int IndexPerQuad = 6;	// Indices needed to create a quad
		double Pi = 3.14159265358979323846;
		// Angles to keep track of the sphere points 
		float Phi = 0.0f;
		float Theta = 0.0f;

		// Create the vertex array to hold the correct number of elements based on the fidelity of the sphere
		int VertexCount = _fidelity * _fidelity * VertexAttrib;
		std::vector<GLfloat> Vertices;

		// Each cycle moves down on the vertical (Y axis) to start the next ring
		for (int i = 0; i < _fidelity; i++)
		{
			// A new  horizontal ring starts at 0 degrees
			Theta = 0.0f;

			// Creates a horizontal ring and adds each new vertex point to the vertex array
			for (int j = 0; j < _fidelity; j++)
			{
				// Calculate the new vertex position point with the new angles
				float x = cos(Phi) * sin(Theta);
				float y = cos(Theta);
				float z = sin(Phi) * sin(Theta);

				// Set the position of the current vertex point
				Vertices.push_back(x * _radius);
				Vertices.push_back(y * _radius);
				Vertices.push_back(z * _radius);

				// Set the texture coordinates of the current vertex point
				Vertices.push_back(((float)i / _fidelity) - 1);
				Vertices.push_back(-((float)j / (_fidelity - 1)));

				// Set the normal direction of the current vertex point
				Vertices.push_back(x);
				Vertices.push_back(y);
				Vertices.push_back(z);

				// Theta (Y axis) angle is incremented based on the angle created by number of sections
				// As the sphere is built ring by ring, the theta is only needed to do half the circumferance therefore using just PI
				Theta += ((float)Pi / ((float)_fidelity - 1.0f));
			}

			// Phi angle (X and Z axes) is incremented based on the angle created by the number of sections
			// Angle uses 2*PI to get the full circumference as this layer is built as a full ring
			Phi += (2.0f * (float)Pi) / ((float)_fidelity - 1.0f);
		}

		// Create the index array to hold the correct number of elements based on the fidelity of the sphere
		std::vector<GLuint> Indices;

		for (int i = 0; i < _fidelity; i++)
		{
			for (int j = 0; j < _fidelity; j++)
			{
				// First triangle of the quad
				Indices.push_back((((i + 1) % _fidelity) * _fidelity) + ((j + 1) % _fidelity));
				Indices.push_back((i * _fidelity) + j);
				Indices.push_back((((i + 1) % _fidelity) * _fidelity) + j);

				// Second triangle of the quad
				Indices.push_back((i * _fidelity) + ((j + 1) % _fidelity));
				Indices.push_back((i * _fidelity) + j);
				Indices.push_back((((i + 1) % _fidelity) * _fidelity) + ((j + 1) % _fidelity));
			}
		}

		return MeshData(Vertices, Indices); // Return vertices and indices of the generated sphere mesh
    }
}