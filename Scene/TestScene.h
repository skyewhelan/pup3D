// pup3D - puppy powered engine
// TestScene.h
// A scene for testing engine features
// Skye Whelan

#pragma once
#include "Scene.h"
#include "../Input/InputReceiver.h"

class TestScene : public Scene, public InputReceiver
{
private:
    Camera* m_FreeCam = nullptr;
    Camera* m_OrbitCam = nullptr;
    Camera* m_EyeCam = nullptr;
public:
    TestScene();
    
    void GenerateAssets() override;
    void ConstructScene() override;
    void Update(float _deltaTime) override;
    
    void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) override;
    
};
