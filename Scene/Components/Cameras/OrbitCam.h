#pragma once
#include "Camera.h"

class OrbitCam : public Camera
{
private:
    glm::vec3 m_Origin = {0.0f, 0.0f, 0.0f};
    float m_Speed = 5;
    float m_Radius = 10;
    float m_OrbitTime = 0.0f;
    
public:
    OrbitCam();
    OrbitCam(glm::vec3 _origin, float _speed, float _radius);
    
    void Update(float _deltaTime) override;
};
