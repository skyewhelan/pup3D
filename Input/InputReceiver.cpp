// pup3D - puppy powered engine
// InputReceiver.cpp
// 
// Skye Whelan

#include "InputReceiver.h"
#include "Input.h"

InputReceiver::InputReceiver()
{
    Input::AddReceiver(this);
}

InputReceiver::~InputReceiver()
{
    Input::RemoveReceiver(this);
}

void InputReceiver::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
}

void InputReceiver::MouseMoveCallback(GLFWwindow* _window, double _x, double _y)
{
}

void InputReceiver::MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods)
{
}

void InputReceiver::ScrollCallback(GLFWwindow* _window, double _deltaX, double _deltaY)
{
    
}
