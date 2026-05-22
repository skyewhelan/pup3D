// pup3D - puppy powered engine
// Actor.cpp
// 
// Skye Whelan

#include "Actor.h"
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

Actor::Actor()
{
    m_Root = new TransformComponent();
}

Actor::~Actor()
{
}

TransformComponent* Actor::GetRoot()
{
    return m_Root;
}

Component* Actor::AttachComponent(Component* _component, Component* _attachPoint)
{
    _component->AttachTo(this, _attachPoint);
    return _component;
}

void Actor::Update(float _deltaTime)
{
    m_Root->Update(_deltaTime);
}

void Actor::Render()
{
    m_Root->Render();
}

glm::vec3 Actor::GetPosition()
{
    return m_Root->GetLocalPosition();
}

glm::vec3 Actor::GetRotation()
{
    return m_Root->GetLocalRotation();
}

glm::vec3 Actor::GetScale()
{
    return m_Root->GetLocalScale();
}

void Actor::SetPosition(glm::vec3 _position)
{
    m_Root->SetLocalPosition(_position);
}

void Actor::SetRotation(glm::vec3 _rotation)
{
    m_Root->SetLocalRotation(_rotation);
}

void Actor::SetScale(glm::vec3 _scale)
{
    m_Root->SetLocalScale(_scale);
}
