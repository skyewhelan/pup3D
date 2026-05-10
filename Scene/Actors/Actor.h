// pup3D - puppy powered engine
// Actor.h
// Actors are objects in 3D space used to construct a scene
// Skye Whelan

#pragma once
#include "../../Assets/Mesh.h"
#include "../../Assets/Shader.h"

class Actor
{
private:
    Mesh* m_Mesh = nullptr;
    GLuint m_ShaderProgram;
    
public:
    Actor(Mesh* _mesh, GLuint _shaderProgram);
    ~Actor();
    
    void SetMesh(Mesh* _mesh);
    void SetShaderProgram(GLuint _shaderProgram);
    
    Mesh* GetMesh();
    GLuint GetShaderProgram();
    
    virtual void Update(float _deltaTime);
    virtual void Render(GLFWwindow* _window);
};
