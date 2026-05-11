// pup3D - puppy powered engine
// Actor.h
// Actors are objects in 3D space used to construct a scene
// Skye Whelan

#pragma once
#include "../../Assets/Mesh.h"
#include "../../Assets/Texture.h"
#include "../../Assets/Shader.h"
#include "../Misc/Camera.h"
#include <glm.hpp>

class Actor
{
protected:
    Mesh* m_Mesh = nullptr;
    Texture* m_Texture = nullptr;
    GLuint m_ShaderProgram;
    
    glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_Rotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_Scale = { 1.0f, 1.0f, 1.0f };
    
    glm::mat4 m_Model = glm::mat4(1.0f);
    
public:
    Actor(Mesh* _mesh, Texture* _texture, GLuint _shaderProgram);
    ~Actor();
    
    void SetMesh(Mesh* _mesh);
    void SetTexture(Texture* _texture);
    void SetShaderProgram(GLuint _shaderProgram);
    
    Mesh* GetMesh();
    Texture* GetTexture();
    GLuint GetShaderProgram();
    
    void SetPosition(glm::vec3 _position);
    void Rotate(glm::vec3 _rotation);
    
    virtual void Update(float _deltaTime);
    virtual void Render(GLFWwindow* _window, Camera* _camera);
};
