// pup3D - puppy powered engine
// main.cpp
// Runs the program
// Skye Whelan

#include <iostream>
#include <glew.h>
#include <glfw3.h>

#include "Manager.h"

int main()
{
    Manager* AppManager = new Manager();
    AppManager->Initialize();
    
    glfwTerminate();
    return 0;
}