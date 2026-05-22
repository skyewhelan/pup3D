#include "FreeCam.h"
#include "../../Input/Input.h"

FreeCam::FreeCam()
{
}

void FreeCam::Update(float _deltaTime)
{
    if (Input::IsKeyPressed(GLFW_KEY_W))
    {
        m_Position += m_Forward * m_Speed * _deltaTime;
    }
    if (Input::IsKeyPressed(GLFW_KEY_S))
    {
        m_Position -= m_Forward * m_Speed * _deltaTime;
    }
    if (Input::IsKeyPressed(GLFW_KEY_A))
    {
        m_Position -= m_Right * m_Speed * _deltaTime;
    }
    if (Input::IsKeyPressed(GLFW_KEY_D))
    {
        m_Position += m_Right * m_Speed * _deltaTime;
    }
    if (Input::IsKeyPressed(GLFW_KEY_Q))
    {
        m_Position += glm::vec3(0.0f, 1.0f, 0.0f) * m_Speed * _deltaTime;
    }
    if (Input::IsKeyPressed(GLFW_KEY_E))
    {
        m_Position -= glm::vec3(0.0f, 1.0f, 0.0f) * m_Speed * _deltaTime;
    }
    
    EyeCam::Update(_deltaTime);
}
