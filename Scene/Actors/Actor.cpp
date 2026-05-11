// pup3D - puppy powered engine
// Actor.cpp
// 
// Skye Whelan

#include "Actor.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Actor::Actor(Mesh* _mesh, Texture* _texture, GLuint _shaderProgram)
{
    m_Mesh = _mesh;
    m_Texture = _texture;
    m_ShaderProgram = _shaderProgram;
}

Actor::~Actor()
{
}

void Actor::SetMesh(Mesh* _mesh)
{
    m_Mesh = _mesh;
}

void Actor::SetTexture(Texture* _texture)
{
    m_Texture = _texture;
}

void Actor::SetShaderProgram(GLuint _shaderProgram)
{
    m_ShaderProgram = _shaderProgram;
}

Mesh* Actor::GetMesh()
{
    return m_Mesh;
}

Texture* Actor::GetTexture()
{
    return m_Texture;
}

GLuint Actor::GetShaderProgram()
{
    return m_ShaderProgram;
}

void Actor::SetPosition(glm::vec3 _position)
{
    m_Position = _position;
}

void Actor::Rotate(glm::vec3 _rotation)
{
    m_Rotation += _rotation;
}

void Actor::Update(float _deltaTime)
{
    m_Model = glm::mat4(1.0f);
    
    // Scale
    m_Model = glm::scale(m_Model, m_Scale);
    // Rotate
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.x), { 1.0f, 0.0f, 0.0f });
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.y), { 0.0f, 1.0f, 0.0f });
    m_Model = glm::rotate(m_Model, glm::radians(m_Rotation.z), { 0.0f, 0.0f, 1.0f });
    // Translate
    m_Model = glm::translate(m_Model, m_Position);
}

void Actor::Render(GLFWwindow* _window, Camera* _camera)
{
    // Texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_Texture->GetID());
    // Shaders
    glUseProgram(m_ShaderProgram);
    // Uniforms
    glUniform1i(glGetUniformLocation(m_ShaderProgram, "Texture"), 0);
    glm::mat4 PVM = _camera->GetProjection() * _camera->GetView() * m_Model;
    glUniformMatrix4fv(glGetUniformLocation(m_ShaderProgram, "PVM"), 1, GL_FALSE, glm::value_ptr(PVM));
    // Mesh
    m_Mesh->Render();
}
