#include "RenderSettings.h"

#include "Framebuffer.h"
#include <iostream>
#include <stb_image.h>

RenderSettings::RenderSettings()
{
}

RenderSettings& RenderSettings::GetInstance()
{
    static RenderSettings Instance;
    return Instance;
}

int RenderSettings::Initialize()
{
    RenderSettings& Instance = GetInstance();
    Instance.m_Monitor = glfwGetPrimaryMonitor();
    
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    // Multisampling resolution
    glfwWindowHint(GLFW_SAMPLES, 4);
    
    
    if (Instance.m_IsBorderless)
    {
        const GLFWvidmode* Mode = glfwGetVideoMode(Instance.m_Monitor);
        glfwWindowHint(GLFW_RED_BITS, Mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, Mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, Mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, Mode->refreshRate);
        
        Instance.m_OutputResolution = {Mode->width, Mode->height};
        
        Instance.m_Window = glfwCreateWindow(Mode->width, Mode->height, "pup3D - Puppy Powered Engine", Instance.m_Monitor, NULL);
    }
    else
    {
        Instance.m_Window = glfwCreateWindow(Instance.m_OutputResolution.x, Instance.m_OutputResolution.y, "pup3D - Puppy Powered Engine", NULL, NULL);
    }
    
    if (!Instance.m_Window)
    {
        std::cout << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(Instance.m_Window);
    
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW\n";
        system("pause");
        glfwTerminate();
        return -1;
    }
    
    int Width;
    int Height;
    glfwGetWindowSize(Instance.m_Window, &Width, &Height);
    std::cout << Width << " " << Height << "\n";
    glViewport(0, 0, Width, Height);
    
    // Flip textures to correct orientation
    stbi_set_flip_vertically_on_load(true);
    
    // Backface culling
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    
    // Depth testing
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    // Stencil Testing
    //glEnable(GL_STENCIL_TEST);
    
    // Blending
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  
    
    // Multisampling
    glEnable(GL_MULTISAMPLE);
    
    // VSync
    glfwSwapInterval(1);
    
    // Framebuffer
    Instance.m_Framebuffer = new Framebuffer();
}

void RenderSettings::SetFogColor(glm::vec4 _color)
{
    GetInstance().m_FogColor = _color;
}

void RenderSettings::SetFogEnabled(bool _enabled)
{
    GetInstance().m_FogEnabled = _enabled;
}

void RenderSettings::SetRenderCamera(Camera* _camera)
{
    GetInstance().m_RenderCamera = _camera;
}

void RenderSettings::SetBorderless(bool _borderless)
{
    
}

void RenderSettings::SetWireframe(bool _wireframe)
{
    RenderSettings& Instance = GetInstance();
    if (_wireframe)
    {
        Instance.m_IsWireframe = true;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
    else
    {
        Instance.m_IsWireframe = false;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
}

bool RenderSettings::AddPointLight(PointLight* _pointLight)
{
    RenderSettings& Instance = GetInstance();
    if ((int)Instance.m_PointLights.size() < Instance.m_MaxPointLights)
    {
        GetInstance().m_PointLights.push_back(_pointLight);
        return true;
    }
    
    std::cout << "Exceeded maximum allowed point lights" << "\n";
    return false;
}

GLFWwindow* RenderSettings::GetWindow()
{
    return GetInstance().m_Window;
}

GLFWmonitor* RenderSettings::GetMonitor()
{
    return GetInstance().m_Monitor;
}

Framebuffer* RenderSettings::GetFramebuffer()
{
    return GetInstance().m_Framebuffer;
}

Camera* RenderSettings::GetRenderCamera()
{
    return GetInstance().m_RenderCamera;
}

glm::ivec2 RenderSettings::GetRenderResolution()
{
    return GetInstance().m_RenderResolution;
}

glm::ivec2 RenderSettings::GetOutputResolution()
{
    return GetInstance().m_OutputResolution;
}

GLint RenderSettings::GetRenderTextureFilter()
{
    return GetInstance().m_RenderTextureFilter;
}

int RenderSettings::GetSamples()
{
    return GetInstance().m_Samples;
}

glm::vec4 RenderSettings::GetFogColor()
{
    return GetInstance().m_FogColor;
}

bool RenderSettings::IsFogEnabled()
{
    return GetInstance().m_FogEnabled;
}

bool RenderSettings::IsBorderless()
{
    return GetInstance().m_IsBorderless;
}

bool RenderSettings::IsWireframe()
{
    return GetInstance().m_IsWireframe;
}

int RenderSettings::GetMaxPointLights()
{
    return GetInstance().m_MaxPointLights;
}

PointLight* RenderSettings::GetPointLight(int _lightIndex)
{
    return GetInstance().m_PointLights[_lightIndex];
}

std::vector<PointLight*> RenderSettings::GetPointLights()
{
    return GetInstance().m_PointLights;
}
