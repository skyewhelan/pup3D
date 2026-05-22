// pup3D - puppy powered engine
// MeshComponent.cpp
// 
// Skye Whelan

#include "MeshComponent.h"

#include <gtc/type_ptr.hpp>

#include "../../Assets/Material.h"
#include "../../Assets/MeshAsset.h"
#include "../../Assets/Shader.h"
#include "../../Assets/TextureAsset.h"
#include "../../Core/RenderSettings.h"
#include "Cameras/Camera.h"
#include "PointLight.h"

MeshComponent::MeshComponent(MeshAsset* _mesh, TextureAsset* _texture, GLuint _shaderProgram)
{
    m_Type = Type::MESH;
    m_Mesh = _mesh;
    m_Texture = _texture;
    m_ShaderProgram = _shaderProgram;
}

MeshComponent::MeshComponent(MeshAsset* _mesh, Material* _material)
{
    m_Type = Type::MESH;
    m_Mesh = _mesh;
    m_Material = _material;
    m_ShaderProgram = m_Material->GetShaderProgram();
}

void MeshComponent::Update(float _deltaTime)
{
    TransformComponent::Update(_deltaTime);
}

void MeshComponent::Render()
{
    Camera* Cam = RS::GetRenderCamera();
    
    // Texture
    if (m_Material->GetTexture())
    {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, m_Material->GetTexture()->GetID());
    }
    // Shaders
    glUseProgram(m_ShaderProgram);
    // Uniforms
    Shader::UniformMat4(m_ShaderProgram, "PVM", Cam->GetProjection() * Cam->GetView() * m_Model);
    Shader::UniformMat4(m_ShaderProgram, "Model", m_Model);
    
    m_Material->SetUniforms();
    if (m_Material->IsLit())
    {
        int LightCount = RS::GetPointLights().size();
        for (int i = 0; i < LightCount; i++)
        {
            PointLight::SetUniforms(m_ShaderProgram, i);
            Shader::UniformI(m_ShaderProgram, "PointLightCount", LightCount);
            Shader::UniformVec3(m_ShaderProgram, "CameraPosition", Cam->GetPosition());
            Shader::UniformVec4(m_ShaderProgram, "BaseAmbientLight", {0.3f, 0.0f, 1.0f, 0.1f});
        }
        
        Shader::UniformVec4 (m_ShaderProgram, "FogColor", RS::GetFogColor());
        Shader::UniformI(m_ShaderProgram, "IsFogEnabled", 1);
    }
    
    
    // Mesh
    m_Mesh->Render();
    
    TransformComponent::Render();
}

MeshAsset* MeshComponent::GetMesh()
{
    return m_Mesh;
}

TextureAsset* MeshComponent::GetTexture()
{
    return m_Texture;
}

GLuint MeshComponent::GetShaderProgram()
{
    return m_ShaderProgram;
}

void MeshComponent::SetMesh(MeshAsset* _mesh)
{
    m_Mesh = _mesh;
}

void MeshComponent::SetTexture(TextureAsset* _texture)
{
    m_Texture = _texture;
}

void MeshComponent::SetShaderProgram(GLuint _shaderProgram)
{
    m_ShaderProgram = _shaderProgram;
}
