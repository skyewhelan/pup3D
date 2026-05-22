#include "OrbitCam.h"

#include <glfw3.h>

OrbitCam::OrbitCam()
{
}

OrbitCam::OrbitCam(glm::vec3 _origin, float _speed, float _radius)
{
    m_Origin = _origin;
    m_Speed = _speed;
    m_Radius = _radius;
}

void OrbitCam::Update(float _deltaTime)
{
    m_OrbitTime = std::fmod(m_OrbitTime + (_deltaTime * m_Speed), 360.0f);
    
    //m_Position = {sin(glfwGetTime()) * 10, 0.0f, cos(glfwGetTime()) * 10};
    m_Position = m_Origin + glm::vec3(sin(m_OrbitTime) * m_Radius, 0.0f, cos(m_OrbitTime) * m_Radius);
    m_Forward = m_Origin - m_Position;
    Camera::Update(_deltaTime);
}
