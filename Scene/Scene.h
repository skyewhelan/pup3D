// pup3D - puppy powered engine
// Scene.h
// A scene is like a level, a 3D environment made up of various objects
// Skye Whelan

#pragma once
#include <map>
#include "Actors/Actor.h"
#include "Misc/Camera.h"

class Scene
{
protected:
    // Camera through which the scene is rendered
    Camera* m_MainCamera = nullptr;
    // Actors in the scene, mapped to names
    std::map<std::string, Actor*> m_Actors;
    // Meshes used by the scene, mapped to names
    std::map<std::string, Mesh*> m_Meshes;
    // Textures used by the scene, mapped to names
    std::map<std::string, Texture*> m_Textures;
    // Shader Programs used in the scene, mapped to names
    std::map<std::string, GLuint> m_ShaderPrograms;
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
    Mesh* GetMesh(std::string _name);
    Texture* GetTexture(std::string _name);
    GLuint GetShaderProgram(std::string _name);
    
    Actor* AddActor(std::string _name, Actor* _actor);
    Mesh* AddMesh(std::string _name, Mesh* _mesh);
    Texture* AddTexture(std::string _name, Texture* _texture);
    GLuint AddShaderProgram(std::string _name, GLuint _shaderProgram);
};
