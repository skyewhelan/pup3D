#pragma once
#include "EyeCam.h"

class FreeCam : public EyeCam
{
    float m_Speed = 10;
public:
    FreeCam();
    
    void Update(float _deltaTime) override;
};
