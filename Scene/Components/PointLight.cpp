#include "PointLight.h"

#include "../../Core/RenderSettings.h"
#include "../../Assets/Shader.h"
#include <format>

PointLight::PointLight()
{
    RenderSettings::AddPointLight(this);
}

PointLight::PointLight(glm::vec3 _color, float _strength)
{
    m_Color = _color;
    m_Strength = _strength;
    RenderSettings::AddPointLight(this);
}

void PointLight::SetUniforms(GLuint _shaderProgram, int _lightIndex)
{
    PointLight* Light = RS::GetPointLight(_lightIndex);
    Shader::UniformVec3(_shaderProgram, std::format("PointLights[{}].Position", _lightIndex), Light->GetWorldPosition());
    Shader::UniformVec3(_shaderProgram, std::format("PointLights[{}].Color", _lightIndex), Light->GetColor());
    Shader::UniformF(_shaderProgram, std::format("PointLights[{}].LightStrength", _lightIndex), Light->GetStrength());
    Shader::UniformF(_shaderProgram, std::format("PointLights[{}].AmbientContribution", _lightIndex), Light->GetAmbientContribution());
    Shader::UniformF(_shaderProgram, std::format("PointLights[{}].AttenuationConstant", _lightIndex), Light->GetAttenuationConstant());
    Shader::UniformF(_shaderProgram, std::format("PointLights[{}].AttenuationLinear", _lightIndex), Light->GetAttenuationLinear());
    Shader::UniformF(_shaderProgram, std::format("PointLights[{}].AttenuationExponent", _lightIndex), Light->GetAttenuationExponent());
}

glm::vec3 PointLight::GetColor() const
{
    return m_Color;
}

float PointLight::GetStrength() const
{
    return m_Strength;
}

float PointLight::GetAmbientContribution() const
{
    return m_AmbientContribution;
}

float PointLight::GetAttenuationConstant() const
{
    return m_AttenuationConstant;
}

float PointLight::GetAttenuationLinear() const
{
    return m_AttenuationLinear;
}

float PointLight::GetAttenuationExponent() const
{
    return m_AttenuationExponent;
}
