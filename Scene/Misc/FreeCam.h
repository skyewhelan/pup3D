#pragma once
#include "Camera.h"

class FreeCam : public Camera
{
    
    float m_Speed;
public:
    FreeCam();
    
    void Update(float _deltaTime) override;
};
