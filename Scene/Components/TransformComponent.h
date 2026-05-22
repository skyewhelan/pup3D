// pup3D - puppy powered engine
// TransformComponent.h
// A component that defines a transform. All actors require one of these as the root component
// Skye Whelan

#pragma once
#include "Component.h"
#include <glm.hpp>

class TransformComponent : public Component
{
protected:
    glm::vec3 m_LocalPosition = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_LocalRotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_LocalScale = { 1.0f, 1.0f, 1.0f };
    
    glm::vec3 m_WorldPosition = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_WorldRotation = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_WorldScale = { 1.0f, 1.0f, 1.0f };
    glm::mat4 m_Model;
    
public:
    TransformComponent();
    
    void Update(float _deltaTime) override;
    
    glm::vec3 GetLocalPosition();
    glm::vec3 GetLocalRotation();
    glm::vec3 GetLocalScale();
    
    glm::vec3 GetWorldPosition();
    glm::vec3 GetWorldRotation();
    glm::vec3 GetWorldScale();
    glm::mat4 GetModel();
    
    TransformComponent* GetParentTransform();
    
    void SetLocalPosition(glm::vec3 _position);
    void SetLocalRotation(glm::vec3 _rotation);
    void SetLocalScale(glm::vec3 _scale);
};
