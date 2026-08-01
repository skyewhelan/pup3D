// pup3D - puppy powered engine
// FreeCam.cpp
// 
// Skye Whelan

#include "FreeCam.h"
#include "../../Input/Input.h"

FreeCam::FreeCam()
{
}

void FreeCam::Update(float _deltaTime)
{
    float DeltaForward = (float)Input::IsKeyPressed(GLFW_KEY_W);
    DeltaForward -= (float)Input::IsKeyPressed(GLFW_KEY_S);
    
    float DeltaRight = Input::IsKeyPressed(GLFW_KEY_D);
    DeltaRight -= Input::IsKeyPressed(GLFW_KEY_A);
    
    float DeltaUp = Input::IsKeyPressed(GLFW_KEY_Q);
    DeltaUp -= Input::IsKeyPressed(GLFW_KEY_E);
    
    glm::vec3 DeltaPosition = ((m_Forward * DeltaForward) + (m_Right * DeltaRight) + (glm::vec3(0.0f, 1.0f, 0.0f)) * DeltaUp);
    m_LocalPosition += DeltaPosition * m_Speed * _deltaTime;
    //
    // if (Input::IsKeyPressed(GLFW_KEY_W))
    // {
    //     m_LocalPosition += m_Forward * m_Speed * _deltaTime;
    // }
    // if (Input::IsKeyPressed(GLFW_KEY_S))
    // {
    //     m_LocalPosition -= m_Forward * m_Speed * _deltaTime;
    // }
    // if (Input::IsKeyPressed(GLFW_KEY_A))
    // {
    //     m_LocalPosition -= m_Right * m_Speed * _deltaTime;
    // }
    // if (Input::IsKeyPressed(GLFW_KEY_D))
    // {
    //     m_LocalPosition += m_Right * m_Speed * _deltaTime;
    // }
    // if (Input::IsKeyPressed(GLFW_KEY_Q))
    // {
    //     m_LocalPosition += glm::vec3(0.0f, 1.0f, 0.0f) * m_Speed * _deltaTime;
    // }
    // if (Input::IsKeyPressed(GLFW_KEY_E))
    // {
    //     m_LocalPosition -= glm::vec3(0.0f, 1.0f, 0.0f) * m_Speed * _deltaTime;
    // }
    
    EyeCam::Update(_deltaTime);
}
