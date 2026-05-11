#include "FreeCam.h"
#include "../../Input/Input.h"

FreeCam::FreeCam()
{
}

void FreeCam::Update(float _deltaTime)
{
    float Speed = 10 * _deltaTime;
    if (Input::IsKeyPressed(GLFW_KEY_W))
    {
        m_Position += m_Forward * Speed;
    }
    if (Input::IsKeyPressed(GLFW_KEY_S))
    {
        m_Position -= m_Forward * Speed;
    }
    if (Input::IsKeyPressed(GLFW_KEY_A))
    {
        m_Position -= m_Right * Speed;
    }
    if (Input::IsKeyPressed(GLFW_KEY_D))
    {
        m_Position += m_Right * Speed;
    }
    if (Input::IsKeyPressed(GLFW_KEY_Q))
    {
        m_Position += m_Up * Speed;
    }
    if (Input::IsKeyPressed(GLFW_KEY_E))
    {
        m_Position -= m_Up * Speed;
    }
    
    Camera::Update(_deltaTime);
}
