#pragma once
#include "Camera.h"
#include "../../Input/InputReceiver.h"

class EyeCam : public Camera, public InputReceiver
{
protected:
    bool m_AllowZoom = true;
    float m_Sensitivity = 0.1f;
    
    float m_Pitch = 0.0f;
    float m_Yaw = -90.0f;
    float m_Roll = 0.0f;
    
    glm::vec2 m_MousePos = { 0.0f, 0.0f };
    glm::vec2 m_LastMousePos = { 0.0f, 0.0f };
    bool m_HasFocus = false;
    
public:
    EyeCam();
    void Update(float _deltaTime) override;
    
    void MouseMoveCallback(GLFWwindow* _window, double _x, double _y) override;
    void ScrollCallback(GLFWwindow* _window, double _deltaX, double _deltaY) override;
};
