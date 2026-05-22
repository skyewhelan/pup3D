// pup3D - puppy powered engine
// Input.h
// Singleton to manage all input events and polling, sends events to input receivers
// Skye Whelan

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <vector>

class InputReceiver;

class Input
{
private:
    
    bool m_IsInputFrozen = false; // Is input currently frozen
    std::vector<InputReceiver*> m_Receivers; // List of active input receivers
    GLFWwindow* m_Window = nullptr; // Window pointer
    bool m_KeyStates[350];
    
    Input();
    static Input& GetInstance(); // Get the singleton instance
public:
    
    static void Initialize(GLFWwindow* _window); // Initialise input system
    static void AddReceiver(InputReceiver* _receiver); // Add an input receiver
    static void RemoveReceiver(InputReceiver* _receiver); // Remove an input receiver
    
    static bool IsKeyPressed(int _key); // Check if a key is pressed
    
    // Send key events to input receivers
    static void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
    // Send mouse movement events to input receivers
    static void MouseMoveCallback(GLFWwindow* _window, double _x, double _y);
    // Send mouse button events to input receivers
    static void MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods);
    // Send scroll wheel events to input receivers
    static void ScrollCallback(GLFWwindow* _window, double _deltaX, double _deltaY);
    
    static bool IsInputFrozen(); // Check if input is frozen
    static void ToggleInput(); // Toggle whether or not input is frozen
    
    Input(const Input&) = delete; // Singletons should not be assignable
    void operator=(const Input&) = delete; // Singletons should not be cloneable
    

};
