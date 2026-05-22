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
        EachActor.second->Render();
    }
    if (m_Skybox)
    {
        m_Skybox->Render();
    }
}

Actor* Scene::GetActor(std::string _name)
{
    return m_Actors[_name];
}

MeshAsset* Scene::GetMesh(std::string _name)
{
    return m_Meshes[_name];
}

TextureAsset* Scene::GetTexture(std::string _name)
{
    return m_Textures[_name];
}

GLuint Scene::GetShaderProgram(std::string _name)
{
    return m_ShaderPrograms[_name];
}

Material* Scene::GetMaterial(std::string _name)
{
    return m_Materials[_name];
}

Actor* Scene::AddActor(std::string _name, Actor* _actor)
{
    m_Actors.insert({ _name, _actor });
    return _actor;
}

MeshAsset* Scene::AddMesh(std::string _name, MeshAsset* _mesh)
{
    m_Meshes.insert({ _name, _mesh });
    return _mesh;
}

TextureAsset* Scene::AddTexture(std::string _name, TextureAsset* _texture)
{
    m_Textures.insert({ _name, _texture });
    return _texture;
}

GLuint Scene::AddShaderProgram(std::string _name, GLuint _shaderProgram)
{
    m_ShaderPrograms.insert({ _name, _shaderProgram });
    return _shaderProgram;
}

Material* Scene::AddMaterial(std::string _name, Material* _material)
{
    m_Materials.insert({ _name, _material });
    return _material;
}
