// pup3D - puppy powered engine
// Camera.h
// Defines a camera through which the scene can be rendered and viewed
// Skye Whelan

#pragma once
#include <glm.hpp>

#include "../TransformComponent.h"

class Camera : public TransformComponent
{
protected:
    float m_FOV = 70.0f;
    
    glm::vec3 m_Forward = { 0.0f, 0.0f, -1.0f };
    glm::vec3 m_Up = { 0.0f, 0.0f, 0.0f };
    glm::vec3 m_Right = { 0.0f, 0.0f, 0.0f };
    
    glm::mat4 m_View;
    glm::mat4 m_Projection;
public:
    Camera();
    ~Camera();
    
    virtual void Update(float _deltaTime);
    
    void SetLocalPosition(glm::vec3 _position);
    void SetForward(glm::vec3 _forward);
    
    glm::vec3 GetLocalPosition();
    glm::vec3 GetForward();
    glm::vec3 GetUp();
    glm::vec3 GetRight();
    glm::mat4 GetView();
    glm::mat4 GetProjection();
};
