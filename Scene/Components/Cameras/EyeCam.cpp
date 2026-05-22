// pup3D - puppy powered engine
// EyeCam.cpp
// 
// Skye Whelan

#include "EyeCam.h"
#include <gtc/matrix_transform.hpp>

EyeCam::EyeCam()
{
}

void EyeCam::Update(float _deltaTime)
{
    m_Forward.x = cos(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    m_Forward.y = sin(glm::radians(m_Pitch));
    m_Forward.z = sin(glm::radians(m_Yaw)) * cos(glm::radians(m_Pitch));
    
    Camera::Update(_deltaTime);
}

void EyeCam::MouseMoveCallback(GLFWwindow* _window, double _x, double _y)
{
    
    InputReceiver::MouseMoveCallback(_window, _x, _y);
    
    m_MousePos = {_x, _y};
    
    if (!m_HasFocus)
    {
        m_LastMousePos = m_MousePos;
        m_HasFocus = true;
    }
    
    glm::vec2 MouseDelta = m_MousePos - m_LastMousePos;
    m_LastMousePos = m_MousePos;
    
    m_Yaw += MouseDelta.x * m_Sensitivity;
    m_Pitch -= MouseDelta.y * m_Sensitivity;
    
    if (m_Pitch > 89.0f) { m_Pitch = 89.0f; }
    if (m_Pitch < -89.0f) { m_Pitch = -89.0f; }
}

void EyeCam::ScrollCallback(GLFWwindow* _window, double _deltaX, double _deltaY)
{
    InputReceiver::ScrollCallback(_window, _deltaX, _deltaY);
    
    if (m_AllowZoom)
    {
        m_FOV -= _deltaY;
    
        if (m_FOV > 70.0f) { m_FOV = 70.0f; }
        if (m_FOV < 1.0f) { m_FOV = 1.0f; }
    
        m_Projection = glm::perspective(glm::radians(m_FOV), 16.0f / 9.0f, 0.1f, 100.0f);
    }
}
