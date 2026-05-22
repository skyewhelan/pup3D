#include "Component.h"
#include "../Actors/Actor.h"
#include "TransformComponent.h"

Component::Component()
{
}

Component::~Component()
{
    
}

void Component::Update(float _deltaTime)
{
    for (Component* Child : m_Children)
    {
        Child->Update(_deltaTime);
    }
}

void Component::Render()
{
    for (Component* Child : m_Children)
    {
        Child->Render();
    }
}

void Component::AttachTo(Actor* _actor, Component* _attachPoint)
{
    m_OwningActor = _actor;
    if (!_attachPoint)
    {
        _attachPoint = m_OwningActor->GetRoot();
    }
    
    _attachPoint->AddChild(this);
    m_Parent = _attachPoint;
}

void Component::Detach()
{
}

void Component::SetActive(bool _active)
{
}

void Component::AddChild(Component* _child)
{
    m_Children.push_back(_child);
}

bool Component::IsActive()
{
    return m_IsActive;
}

Actor* Component::GetOwningActor()
{
    return m_OwningActor;
}

Component* Component::GetParent()
{
    return m_Parent;
}

std::vector<Component*> Component::GetChildren()
{
    return m_Children;
}

std::string Component::GetName()
{
    return m_Name;
}

Component::Type Component::GetType()
{
    return m_Type;
}

bool Component::FindComponentsByName(std::string _name, Component* _root, std::vector<Component*>* _out)
{   
    std::vector<Component*> Queue;
    
    for (Component* Child : _root->GetChildren())
    {
        if (Child->GetName() == _name)
        {
            _out->push_back(Child);
        }
        
        Queue.push_back(Child);
    }
    
    for (Component* Child : Queue)
    {
        FindComponentsByName(_name, Child, _out);
    }
    
    return !_out->empty();
}

bool Component::FindComponentsByType(Type _type, Component* _root, std::vector<Component*>* _out)
{
    std::vector<Component*> Queue;
    
    for (Component* Child : _root->GetChildren())
    {
        if (Child->GetType() == _type)
        {
            _out->push_back(Child);
        }
        
        Queue.push_back(Child);
    }
    
    for (Component* Child : Queue)
    {
        FindComponentsByType(_type, Child, _out);
    }
    
    return !_out->empty();
}
