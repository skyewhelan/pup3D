// pup3D - puppy powered engine
// Scene.cpp
// 
// Skye Whelan

#include "Scene.h"

Scene::Scene()
{
    GenerateAssets();
    ConstructScene();
}

Scene::~Scene()
{
}

void Scene::GenerateAssets()
{
    
}

void Scene::ConstructScene()
{
    
}

void Scene::Update(float _deltaTime)
{
    m_MainCamera->Update(_deltaTime);
    for (auto EachActor : m_Actors)
    {
        EachActor.second->Update(_deltaTime);
    }
}

void Scene::Render(GLFWwindow* _window)
{
    for (auto EachActor : m_Actors)
    {
        EachActor.second->Render(_window, m_MainCamera);
    }
}

Actor* Scene::GetActor(std::string _name)
{
    return m_Actors[_name];
}

Mesh* Scene::GetMesh(std::string _name)
{
    return m_Meshes[_name];
}

Texture* Scene::GetTexture(std::string _name)
{
    return m_Textures[_name];
}

GLuint Scene::GetShaderProgram(std::string _name)
{
    return m_ShaderPrograms[_name];
}

Actor* Scene::AddActor(std::string _name, Actor* _actor)
{
    m_Actors.insert({ _name, _actor });
    return _actor;
}

Mesh* Scene::AddMesh(std::string _name, Mesh* _mesh)
{
    m_Meshes.insert({ _name, _mesh });
    return _mesh;
}

Texture* Scene::AddTexture(std::string _name, Texture* _texture)
{
    m_Textures.insert({ _name, _texture });
    return _texture;
}

GLuint Scene::AddShaderProgram(std::string _name, GLuint _shaderProgram)
{
    m_ShaderPrograms.insert({ _name, _shaderProgram });
    return _shaderProgram;
}
