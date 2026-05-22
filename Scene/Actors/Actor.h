// pup3D - puppy powered engine
// Actor.h
// Actors are objects in 3D space used to construct a scene
// Skye Whelan
#pragma once

#include "../Components/TransformComponent.h"
class Camera;

class Actor
{
protected:
    TransformComponent* m_Root;
    
public:
    Actor();
    ~Actor();
    
    TransformComponent* GetRoot();
    Component* AttachComponent(Component* _component, Component* _attachPoint = nullptr);
    
    virtual void Update(float _deltaTime);
    virtual void Render();
    
    glm::vec3 GetPosition();
    glm::vec3 GetRotation();
    glm::vec3 GetScale();
    
    void SetPosition(glm::vec3 _position);
    void SetRotation(glm::vec3 _rotation);
    void SetScale(glm::vec3 _scale);
};
