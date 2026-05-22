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
    
    // Override to manage key callbacks
    virtual void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
    // Override to manage mouse movement callbacks
    virtual void MouseMoveCallback(GLFWwindow* _window, double _x, double _y);
    // Override to manage mouse button callbacks
    virtual void MouseButtonCallback(GLFWwindow* _window, int _button, int _action, int _mods);
    // Override to manage scroll wheel callbacks
    virtual void ScrollCallback(GLFWwindow* _window, double _deltaX, double _deltaY);
};
