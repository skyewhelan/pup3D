// pup3D - puppy powered engine
// Manager.h
// The core of the application. Handles openGL setup and the update/render loop
// Skye Whelan

#pragma once
#include "../Scene/Scene.h"
#include "../Input/InputReceiver.h"

class Manager :public InputReceiver
{
private:
    bool m_IsBorderless = true; // Is using borderless fullscreen mode
    bool m_IsWireframe = false; // Is using wireframe mode
    int m_WindowedHeight = 720; // Desired height if in windowed mode
    int m_WindowedWidth = 1280; // Desired width if in windowed mode
    int m_ActualHeight = m_WindowedHeight; // Actual current height
    int m_ActualWidth = m_WindowedWidth; // Actual current width
    
    float m_CurrentTime = 0.0f; // Time elapsed since glfw initialisation
    float m_PreviousTime = 0.0f; // CurrentTime as of the previous update step
    float m_DeltaTime = 0.0f; // Time elapsed since the previous update step
    
    Scene* m_ActiveScene = nullptr; // The scene that is currently being rendered
    
    GLFWwindow* m_Window = nullptr; // Current window
    GLFWmonitor* m_Monitor = nullptr; // Current monitor
    
public:
    Manager();
    
    int Initialise(); // Intitalise opengl and associated libraries
    // KeyCallback override; close app on escape
    void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods) override;
    
    void ToggleWireframe(); // Toggle wireframe mode
    
    void Update(); // Update step; runs every frame
    void Render(); // Renders the scene; runs every frame
    
    ~Manager() = default;
};
