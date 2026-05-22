// pup3D - puppy powered engine
// Transform.cpp
// 
// Skye Whelan

#include "TransformComponent.h"
#include <ext/matrix_transform.hpp>

TransformComponent::TransformComponent()
{
    m_Type = Type::TRANSFORM;
}

void TransformComponent::Update(float _deltaTime)
{
    TransformComponent* ParentTransform = GetParentTransform();
    if (ParentTransform != nullptr)
    {
        m_Model = ParentTransform->GetModel();
        m_WorldPosition = ParentTransform->GetWorldPosition() + m_LocalPosition;
        m_WorldRotation = ParentTransform->GetWorldRotation() + m_LocalRotation;
        m_WorldScale = ParentTransform->GetWorldScale() + m_LocalScale;
    }
    else
    {
        m_Model = glm::mat4(1.0f);
        m_WorldPosition = m_LocalPosition;
        m_WorldRotation = m_LocalRotation;
        m_WorldScale = m_LocalScale;
    }
    
    // Scale
    m_Model = glm::scale(m_Model, m_LocalScale);
    // Rotate
    m_Model = glm::rotate(m_Model, glm::radians(m_LocalRotation.x), { 1.0f, 0.0f, 0.0f });
    m_Model = glm::rotate(m_Model, glm::radians(m_LocalRotation.y), { 0.0f, 1.0f, 0.0f });
    m_Model = glm::rotate(m_Model, glm::radians(m_LocalRotation.z), { 0.0f, 0.0f, 1.0f });
    // Translate
    m_Model = glm::translate(m_Model, m_LocalPosition);
    
    Component::Update(_deltaTime);
}

glm::vec3 TransformComponent::GetLocalPosition()
{
    return m_LocalPosition;
}

glm::vec3 TransformComponent::GetLocalRotation()
{
    return m_LocalRotation;
}

glm::vec3 TransformComponent::GetLocalScale()
{
    return m_LocalScale;
}

glm::vec3 TransformComponent::GetWorldPosition()
{
    return m_WorldPosition;
}

glm::vec3 TransformComponent::GetWorldRotation()
{
    return m_WorldRotation;
}

glm::vec3 TransformComponent::GetWorldScale()
{
    return m_WorldScale;
}

glm::mat4 TransformComponent::GetModel()
{
    return m_Model;
}

TransformComponent* TransformComponent::GetParentTransform()
{
    Component* Parent = m_Parent;
    TransformComponent* Cast = nullptr;
    while (Parent != nullptr)
    {
        Cast = dynamic_cast<TransformComponent*>(Parent);
        if (Cast != nullptr)
        {
            return Cast;
        }
        else
        {
            Parent = Parent->GetParent();
        }
    }
    
    return nullptr;
}

void TransformComponent::SetLocalPosition(glm::vec3 _position)
{
    m_LocalPosition = _position;
}

void TransformComponent::SetLocalRotation(glm::vec3 _rotation)
{
    m_LocalRotation = _rotation;
}

void TransformComponent::SetLocalScale(glm::vec3 _scale)
{
    m_LocalScale = _scale;
}
