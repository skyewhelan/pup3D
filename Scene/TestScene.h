// pup3D - puppy powered engine
// TestScene.h
// A scene for testing engine features
// Skye Whelan

#pragma once
#include "Scene.h"

class TestScene : public Scene
{
public:
    TestScene();
    
    void GenerateAssets() override;
    void ConstructScene() override;
    
};
