// pup3D - puppy powered engine
// Input.cpp
//
// Skye Whelan

#include "Input.h"
#include "InputReceiver.h"

Input::Input()
{
}

Input& Input::GetInstance()
{
    static Input Instance;
    return Instance;
}

void Input::Initialize(GLFWwindow* _window)
{
    Input& Instance = GetInstance();
    Instance.m_Window = _window;
    
    glfwSetInputMode(Instance.m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    // Set callbacks
    glfwSetKeyCallback(Instance.m_Window, KeyCallback);
    glfwSetCursorPosCallback(Instance.m_Window, MouseMoveCallback);
    glfwSetMouseButtonCallback(Instance.m_Window, MouseButtonCallback);
    glfwSetScrollCallback(Instance.m_Window, ScrollCallback);
}

void Input::AddReceiver(InputReceiver* _receiver)
{
    GetInstance().m_Receivers.push_back(_receiver);
}

void Input::RemoveReceiver(InputReceiver* _receiver)
{
    std::vector<InputReceiver*>& Receivers = GetInstance().m_Receivers;
    Receivers.erase(std::find(Receivers.begin(), Receivers.end(), _receiver));
}

bool Input::IsKeyPressed(int _key)
{
    return GetInstance().m_KeyStates[_key];
    //return (glfwGetKey(GetInstance().m_Window, _key) == GLFW_PRESS);
}

void Input::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    Input& Instance = GetInstance();
    
    if (_action == GLFW_PRESS)
    {
        Instance.m_KeyStates[_key] = true;
    }
    else if (_action == GLFW_RELEASE)
    {
        Instance.m_KeyStates[_key] = false;
    }
    
    for (InputReceiver* Receiver : Instance.m_Receivers)
    {
        Receiver->KeyCallback(_window, _key, _scancode, _action, _mods);
    }
}

void Input::MouseMoveCallback(GLFWwindow* _window, double _x, double _y)
{
    Input& Instance = GetInstance();
    
    for (InputReceiver* Receiver : Instance.m_Receivers)
    {
        Receiver->MouseMoveCallback(_window, _x, _y);
    }
}

void Input::MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods)
{
    Input& Instance = GetInstance();
    
    for (InputReceiver* Receiver : Instance.m_Receivers)
    {
        Receiver->MouseButtonCallback(_window, _button, _action, _mods);
    }
}

void Input::ScrollCallback(GLFWwindow* _window, double _deltaX, double _deltaY)
{
    Input& Instance = GetInstance();
    
    for (InputReceiver* Receiver : Instance.m_Receivers)
    {
        Receiver->ScrollCallback(_window, _deltaX, _deltaY);
    }
}

bool Input::IsInputFrozen()
{
    return GetInstance().m_IsInputFrozen;
}

void Input::ToggleInput()
{
    Input& Input = GetInstance();
    Input.m_IsInputFrozen = !Input.m_IsInputFrozen;
}
