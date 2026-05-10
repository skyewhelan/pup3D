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
    glfwSetKeyCallback(Instance.m_Window, KeyCallback);
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
    
    return (glfwGetKey(GetInstance().m_Window, _key) == GLFW_PRESS);
}

void Input::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    for (InputReceiver* Receiver : GetInstance().m_Receivers)
    {
        Receiver->KeyCallback(_window, _key, _scancode, _action, _mods);
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
