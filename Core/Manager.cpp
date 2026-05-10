// pup3D - puppy powered engine
// Manager.cpp
// 
// Skye Whelan

#include <iostream>
#include "Manager.h"
#include "../Assets/Shader.h"
#include "../Input/Input.h"
#include "../Scene/TestScene.h"

Manager::Manager()
{
    
}

int Manager::Initialise()
{
    glfwInit();
    
    m_Monitor = glfwGetPrimaryMonitor();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
  
    
    if (m_IsBorderless)
    {
        const GLFWvidmode* Mode = glfwGetVideoMode(m_Monitor);
        glfwWindowHint(GLFW_RED_BITS, Mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, Mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, Mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate);
        
        m_ActualHeight = Mode->height;
        m_ActualWidth = Mode->width;
        
        m_Window = glfwCreateWindow(m_ActualWidth, m_ActualHeight, "OpenGL Playground", m_Monitor, NULL);
    }
    else
    {
        m_Window = glfwCreateWindow(m_WindowedWidth, m_WindowedHeight, "OpenGL Playground", NULL, NULL);
    }
    
    if (!m_Window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(m_Window);
    
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW\n";
        system("pause");
        glfwTerminate();
        return -1;
    }
    
    glViewport(0, 0, m_ActualWidth, m_ActualHeight);
    
    // Backface culling
    //glCullFace(GL_BACK);
    //glEnable(GL_CULL_FACE);
    
    Input::Initialize(m_Window);
    
    m_ActiveScene = new TestScene();
    
    
    while (!glfwWindowShouldClose(m_Window))
    {
        Update();
        Render();
    }
    
    return 1;
}

void Manager::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    InputReceiver::KeyCallback(_window, _key, _scancode, _action, _mods);
    
    if (_key == GLFW_KEY_ESCAPE &&  _action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(_window, GLFW_TRUE);
    }
}

void Manager::ToggleWireframe()
{
    m_IsWireframe = !m_IsWireframe;
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Manager::Update()
{
    m_PreviousTime = m_CurrentTime;
    m_CurrentTime = glfwGetTime();
    m_DeltaTime = m_CurrentTime - m_PreviousTime;
    glfwPollEvents();
    
    m_ActiveScene->Update(m_DeltaTime);
}

void Manager::Render()
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    m_ActiveScene->Render(m_Window);
    
    glfwSwapBuffers(m_Window);
}
