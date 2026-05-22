// pup3D - puppy powered engine
// Material.cpp
// 
// Skye Whelan

#pragma optimize("", off)
#include "Material.h"
#include "Shader.h"
#include "TextureAsset.h"
Material::Material(TextureAsset* _texture, GLuint _shaderProgram, bool _lit)
{    
    m_Texture = _texture;
    m_ShaderProgram = _shaderProgram;
    m_IsLit = _lit;
    
    AddParamVec4("Albedo", {1.0f, 1.0f, 1.0f, 1.0f});
    
    if (m_Texture)
    {
        AddParamInt("Texture", 0);
    }
    
    if (m_IsLit)
    {
        AddParamFloat("AmbientMult", 1.0f);
        AddParamFloat("Roughness", 0.01f);
        AddParamFloat("Shininess", 0.5f);
    }
}

void Material::SetUniforms()
{
    for (auto IntParam : m_ParamsInt)
    {
        Shader::UniformI(m_ShaderProgram, "Material." + IntParam.first, IntParam.second);
    }
    
    for (auto FloatParam : m_ParamsFloat)
    {
        Shader::UniformF(m_ShaderProgram, "Material." + FloatParam.first, FloatParam.second);
    }
    
    for (auto Vec3Param : m_ParamsVec3)
    {
        Shader::UniformVec3(m_ShaderProgram, "Material." + Vec3Param.first, Vec3Param.second);
    }
    
    for (auto Vec4Param : m_ParamsVec4)
    {
        Shader::UniformVec4(m_ShaderProgram, "Material." + Vec4Param.first, Vec4Param.second);
    }
    
    for (auto Mat4Param : m_ParamsMat4)
    {
        Shader::UniformMat4(m_ShaderProgram, "Material." + Mat4Param.first, Mat4Param.second);
    }
}

TextureAsset* Material::GetTexture()
{
    return m_Texture;
}

GLuint Material::GetShaderProgram()
{
    return m_ShaderProgram;
}

bool Material::IsLit()
{
    return m_IsLit;
}

void Material::AddParamInt(std::string _name, GLint _value)
{
    m_ParamsInt.insert({_name, _value});
}

void Material::AddParamFloat(std::string _name, GLfloat _value)
{
    m_ParamsFloat.insert({_name, _value});
}

void Material::AddParamVec3(std::string _name, glm::vec3 _value)
{
    m_ParamsVec3.insert({_name, _value});
}

void Material::AddParamVec4(std::string _name, glm::vec4 _value)
{
    m_ParamsVec4.insert({_name, _value});
}

void Material::AddParamMat4(std::string _name, glm::mat4 _value)
{
    m_ParamsMat4.insert({_name, _value});
}

void Material::SetParamInt(std::string _name, GLint _value)
{
    m_ParamsInt.at(_name) = _value;
}

void Material::SetParamFloat(std::string _name, GLfloat _value)
{
    m_ParamsFloat.at(_name) = _value;
}

void Material::SetParamVec3(std::string _name, glm::vec3 _value)
{
    m_ParamsVec3.at(_name) = _value;
}

void Material::SetParamVec4(std::string _name, glm::vec4 _value)
{
    m_ParamsVec4.at(_name) = _value;
}

void Material::SetParamMat4(std::string _name, glm::mat4 _value)
{
    m_ParamsMat4.at(_name) = _value;
}

GLuint Material::GetParamInt(std::string _name)
{
    return m_ParamsInt.at(_name);
}

GLfloat Material::GetParamFloat(std::string _name)
{
    return m_ParamsFloat.at(_name);
}

glm::vec3 Material::GetParamVec3(std::string _name)
{
    return m_ParamsVec3.at(_name);
}

glm::vec4 Material::GetParamVec4(std::string _name)
{
    return m_ParamsVec4.at(_name);
}

glm::mat4 Material::GetParamMat4(std::string _name)
{
    return m_ParamsMat4.at(_name);
}
#pragma optimize("", on)    