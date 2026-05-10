// pup3D - puppy powered engine
// InputReceiver.h
// Classes can inherit from this to receive input events
// Skye Whelan

#pragma once
#include <glew.h>
#include <glfw3.h>

class InputReceiver
{
public:
    InputReceiver();
    virtual ~InputReceiver();
    
    virtual void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
};
