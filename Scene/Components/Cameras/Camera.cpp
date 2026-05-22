// pup3D - puppy powered engine
// Camera.cpp
// 
// Skye Whelan

#include "Camera.h"
#include <gtc/matrix_transform.hpp>

Camera::Camera()
{
    m_Projection = glm::perspective(glm::radians(m_FOV), 16.0f / 9.0f, 0.1f, 500.0f);
}

Camera::~Camera()
{
}

void Camera::Update(float _deltaTime)
{
    m_Right = glm::normalize(glm::cross(m_Forward, {0.0f, 1.0f, 0.0f}));
    m_Up = glm::cross(m_Right, m_Forward);
    
    m_View = glm::lookAt(m_Position, m_Position + m_Forward, m_Up);
}

void Camera::SetPosition(glm::vec3 _position)
{
    m_Position = _position;
}

void Camera::SetForward(glm::vec3 _forward)
{
    m_Forward = _forward;
}

glm::vec3 Camera::GetPosition()
{
    return m_Position;
}

glm::vec3 Camera::GetForward()
{
    return m_Forward;
}

glm::vec3 Camera::GetUp()
{
    return m_Up;
}

glm::vec3 Camera::GetRight()
{
    return m_Right;
}

glm::mat4 Camera::GetView()
{
    return m_View;
}

glm::mat4 Camera::GetProjection()
{
    return m_Projection;
}
