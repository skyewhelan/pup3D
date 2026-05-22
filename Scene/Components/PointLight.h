#pragma once
#include "TransformComponent.h"

class PointLight : public TransformComponent
{
public:
    PointLight();
    PointLight(glm::vec3 _color, float _strength);

    glm::vec3 m_Color = {1.0f, 1.0f, 1.0f};
    float m_Strength = 1.0f;
    float m_AmbientContribution = 0.01f;
    float m_AttenuationConstant = 1.0f;
    float m_AttenuationLinear = 0.027f;
    float m_AttenuationExponent = 0.0028f;
    
    static void SetUniforms(GLuint _shaderProgram, int _lightIndex);
    
    glm::vec3 GetColor() const;
    float GetStrength() const;
    float GetAmbientContribution() const;
    float GetAttenuationConstant() const;
    float GetAttenuationLinear() const;
    float GetAttenuationExponent() const;
};
