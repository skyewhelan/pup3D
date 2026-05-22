// pup3D - puppy powered engine
// MeshComponent.h
// A component responsible for positioning and rendering a mesh
// Skye Whelan

#pragma once
#include "TransformComponent.h"
#include "../../Assets/Material.h"
class MeshAsset;
class TextureAsset;

class MeshComponent : public TransformComponent
{
    MeshAsset* m_Mesh = nullptr;
    TextureAsset* m_Texture = nullptr;
    Material* m_Material = nullptr;
    GLuint m_ShaderProgram;

public:
    MeshComponent(MeshAsset* _mesh, TextureAsset* _texture, GLuint _shaderProgram);
    MeshComponent(MeshAsset* _mesh, Material* _material);
    
    void Update(float _deltaTime) override;
    void Render() override;
    
    MeshAsset* GetMesh();
    TextureAsset* GetTexture();
    GLuint GetShaderProgram();
    
    void SetMesh(MeshAsset* _mesh);
    void SetTexture(TextureAsset* _texture);
    void SetShaderProgram(GLuint _shaderProgram);
};
