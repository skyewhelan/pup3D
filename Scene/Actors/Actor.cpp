// pup3D - puppy powered engine
// Actor.cpp
// 
// Skye Whelan

#include "Actor.h"

Actor::Actor(Mesh* _mesh, GLuint _shaderProgram)
{
    m_Mesh = _mesh;
    m_ShaderProgram = _shaderProgram;
}

Actor::~Actor()
{
}

void Actor::SetMesh(Mesh* _mesh)
{
    m_Mesh = _mesh;
}

void Actor::SetShaderProgram(GLuint _shaderProgram)
{
    m_ShaderProgram = _shaderProgram;
}

Mesh* Actor::GetMesh()
{
    return m_Mesh;
}

GLuint Actor::GetShaderProgram()
{
    return m_ShaderProgram;
}

void Actor::Update(float _deltaTime)
{
}

void Actor::Render(GLFWwindow* _window)
{
    glUseProgram(m_ShaderProgram);
    m_Mesh->Render();
}
