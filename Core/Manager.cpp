// pup3D - puppy powered engine
// Manager.cpp
// 
// Skye Whelan

#include <iostream>
#include "Manager.h"

#include <stb_image.h>

#include "Framebuffer.h"
#include "RenderSettings.h"
#include "../Assets/Shader.h"
#include "../Input/Input.h"
#include "../Scene/TestScene.h"
#include "../Scene/Actors/Terrain.h"

Manager::Manager()
{
    
}

int Manager::Initialize()
{
    glfwInit();
    RenderSettings::Initialize();
    m_Window = RenderSettings::GetWindow();
    
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
    if (_key == GLFW_KEY_F && _action == GLFW_PRESS)
    {
        RenderSettings::SetWireframe(!RenderSettings::IsWireframe());
    }
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
    glm::ivec2 RenderRes = RS::GetRenderResolution();
    glm::ivec2 OutputRes = RS::GetOutputResolution();
    
    Framebuffer* FB = RS::GetFramebuffer();
    glBindFramebuffer(GL_FRAMEBUFFER, FB->GetMultisampleFBO());
    
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0, 0, RenderRes.x, RenderRes.y);
    m_ActiveScene->Render(m_Window);
    
    glBindFramebuffer(GL_READ_FRAMEBUFFER, FB->GetMultisampleFBO());
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, FB->GetIntermediateFBO());
    //glEnable(GL_FRAMEBUFFER_SRGB); 
    glBlitFramebuffer(0, 0, RenderRes.x, RenderRes.y, 0, 0, RenderRes.x, RenderRes.y, GL_COLOR_BUFFER_BIT, GL_NEAREST);
    //glDisable(GL_FRAMEBUFFER_SRGB);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    
    glViewport(0, 0, OutputRes.x, OutputRes.y);
    FB->Render();
    
    glfwSwapBuffers(m_Window);
}
