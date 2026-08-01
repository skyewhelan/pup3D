// pup3D - puppy powered engine
// Scene.cpp
// 
// Skye Whelan

#include "Scene.h"

#include <iostream>

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
    for (auto Pair : m_Actors)
    {
        Pair.second->Update(_deltaTime);
    }
    for (auto Pair : m_Terrains)
    {
        Pair.second->Update(_deltaTime);
    }
}

void Scene::Render(GLFWwindow* _window)
{
    for (auto Pair : m_Actors)
    {
        Pair.second->Render();
    }
    for (auto Pair : m_Terrains)
    {
        Pair.second->Render();
    }
    if (m_Skybox)
    {
        m_Skybox->Render();
    }
}

Actor* Scene::GetActor(std::string _name)
{
    Actor* Get = m_Actors[_name];
    if (!Get)
    {
        std::cout << "GetActor could not find Actor " << _name << " in scene " << m_SceneName << ",  returning nullptr\n";
    }
        
    return Get;
}

Terrain* Scene::GetTerrain(std::string _name)
{
    Terrain* Get = m_Terrains[_name];
    if (!Get)
    {
        std::cout << "GetTerrain could not find Terrain " << _name << " in scene " << m_SceneName << ",  returning nullptr\n";
    }
        
    return Get;
}

MeshAsset* Scene::GetMesh(std::string _name)
{
    
    MeshAsset* Get = m_Meshes[_name];
    if (!Get)
    {
        std::cout << "GetMesh could not find MeshAsset " << _name << " in scene " << m_SceneName << ",  returning nullptr\n";
    }
        
    return Get;
}

TextureAsset* Scene::GetTexture(std::string _name)
{
    TextureAsset* Get = m_Textures[_name];
    if (!Get)
    {
        std::cout << "GetTexture could not find TextureAsset " << _name << " in scene " << m_SceneName << ",  returning nullptr\n";
    }
        
    return Get;
}

GLuint Scene::GetShaderProgram(std::string _name)
{
    return m_ShaderPrograms[_name];
}

Material* Scene::GetMaterial(std::string _name)
{
    Material* Get = m_Materials[_name];
    if (!Get)
    {
        std::cout << "GetMaterial could not find Material " << _name << " in scene " << m_SceneName << ",  returning nullptr\n";
    }
        
    return Get;
}

Actor* Scene::AddActor(std::string _name, Actor* _actor)
{
    m_Actors.insert({ _name, _actor });
    return _actor;
}

Terrain* Scene::AddTerrain(std::string _name, Terrain* _terrain)
{
    m_Terrains.insert({ _name, _terrain });
    return _terrain;
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
