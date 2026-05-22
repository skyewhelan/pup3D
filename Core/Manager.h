// pup3D - puppy powered engine
// Manager.h
// The core of the application. Handles openGL setup and the update/render loop
// Skye Whelan

#pragma once
#include "../Scene/Scene.h"
#include "../Input/InputReceiver.h"

class Terrain;

class Manager :public InputReceiver
{
private:
    
    float m_CurrentTime = 0.0f; // Time elapsed since glfw initialisation
    float m_PreviousTime = 0.0f; // CurrentTime as of the previous update step
    float m_DeltaTime = 0.0f; // Time elapsed since the previous update step
    
    Terrain* m_Terrain = nullptr;
    Scene* m_ActiveScene = nullptr; // The scene that is currently being rendered
    
    GLFWwindow* m_Window = nullptr; // Current window
    
public:
    Manager();
    
    int Initialize(); // Intitialize opengl and associated libraries
    // KeyCallback override; close app on escape
    void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) override;
    
    void Update(); // Update step; runs every frame
    void Render(); // Renders the scene; runs every frame
    
    ~Manager() = default;
};
