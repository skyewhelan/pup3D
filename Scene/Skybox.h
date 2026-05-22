// pup3D - puppy powered engine
// Skybox.h
// An inverted cube displaying a cubemap, rendered behind the scene
// Skye Whelan

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <map>
#include <string>

#include "Components/Cameras/Camera.h"

class Skybox
{
    GLuint m_Cubemap;
    GLuint m_ShaderProgram;
    GLuint m_VBO; // Vertex Buffer Object; Stores vertices
    GLuint m_EBO; // Element Buffer Object; Stores indices
    GLuint m_VAO; // Vertex Array Object
public:
    Skybox(std::string _cubemapPath);
    
    void Render();
};
