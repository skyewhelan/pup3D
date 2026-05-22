// pup3D - puppy powered engine
// FreeCam.h
// An EyeCam which can be moved with WASD input
// Skye Whelan

#pragma once
#include "EyeCam.h"

class FreeCam : public EyeCam
{
    float m_Speed = 10;
public:
    FreeCam();
    
    void Update(float _deltaTime) override;
};
