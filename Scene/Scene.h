// pup3D - puppy powered engine
// Scene.h
// A scene is like a level, a 3D environment made up of various objects
// Skye Whelan

#pragma once
#include <map>
#include <string>

#include "Skybox.h"
#include "../Assets/MeshAsset.h"
#include "../Assets/TextureAsset.h"
#include "Actors/Actor.h"
#include "Components/Cameras/Camera.h"
#include "Actors/Terrain.h"

class Material;

class Scene
{
protected:
    // Camera through which the scene is rendered
    Camera* m_MainCamera = nullptr;
    Skybox* m_Skybox = nullptr;
    // Actors in the scene, mapped to names
    std::map<std::string, Actor*> m_Actors;
    // Terrains in the scene, mapped to names
    std::map<std::string, Terrain*> m_Terrains;
    // Meshes used by the scene, mapped to names
    std::map<std::string, MeshAsset*> m_Meshes;
    // Textures used by the scene, mapped to names
    std::map<std::string, TextureAsset*> m_Textures;
    // Shader Programs used in the scene, mapped to names
    std::map<std::string, GLuint> m_ShaderPrograms;
    // Materials used in the scene, mapped to names
    std::map<std::string, Material*> m_Materials;
public:
    Scene();
    ~Scene();
    
    // Override this: generate meshes, shaders etc. to be used in the scene
    virtual void GenerateAssets();
    // Override this: create and position actors to build the scene
    virtual void ConstructScene();
    // Update actors and perform per-frame processing, override if desired
    virtual void Update(float _deltaTime);
    // Render everything in the scene, override if desired
    virtual void Render(GLFWwindow* _window);
    
    Actor* GetActor(std::string _name);
    Terrain* GetTerrain(std::string _name);
    MeshAsset* GetMesh(std::string _name);
    TextureAsset* GetTexture(std::string _name);
    GLuint GetShaderProgram(std::string _name);
    Material* GetMaterial(std::string _name);
    
    Actor* AddActor(std::string _name, Actor* _actor);
    Terrain* AddTerrain(std::string _name, Terrain* _terrain);
    MeshAsset* AddMesh(std::string _name, MeshAsset* _mesh);
    TextureAsset* AddTexture(std::string _name, TextureAsset* _texture);
    GLuint AddShaderProgram(std::string _name, GLuint _shaderProgram);
    Material* AddMaterial(std::string _name, Material* _material);
};
