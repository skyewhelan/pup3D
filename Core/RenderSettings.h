// pup3D - puppy powered engine
// RenderData.h
// Singleton to store and modify commonly accessed rendering-related data
// Skye Whelan

#pragma once
#include <glew.h>
#include <glfw3.h>
#include <glm.hpp>
#include <vector>

class PointLight;
class Camera;
class Framebuffer;

#define RS RenderSettings

class RenderSettings
{
private:
    // Pointers
    GLFWwindow* m_Window;
    GLFWmonitor* m_Monitor;
    Framebuffer* m_Framebuffer;
    Camera* m_RenderCamera;
    
    // Rendering
    bool m_IsBorderless = true;
    bool m_IsWireframe = false;
    glm::ivec2 m_RenderResolution = {1920, 1080};
    glm::ivec2 m_OutputResolution = {1280, 720};
    GLint m_RenderTextureFilter = GL_LINEAR;
    int m_Samples = 4;
    
    // Lighting/Effects
    glm::vec4 m_FogColor = {1.0f, 1.0f, 1.0f, 1.0f};
    bool m_FogEnabled = true;
    int m_MaxPointLights = 8;
    std::vector<PointLight*> m_PointLights;
    
    RenderSettings();
    static RenderSettings& GetInstance();
public:
    static int Initialize();
    
    static void SetFogColor(glm::vec4 _color);
    static void SetFogEnabled(bool _enabled);
    static void SetRenderCamera(Camera* _camera);
    static void SetBorderless(bool _borderless);
    static void SetWireframe(bool _wireframe);
    static bool AddPointLight(PointLight* _pointLight);
    
    static GLFWwindow* GetWindow();
    static GLFWmonitor* GetMonitor();
    static Framebuffer* GetFramebuffer();
    static Camera* GetRenderCamera();
    static glm::ivec2 GetRenderResolution();
    static glm::ivec2 GetOutputResolution();
    static GLint GetRenderTextureFilter();
    static int GetSamples();
    static glm::vec4 GetFogColor();
    static bool IsFogEnabled();
    static bool IsBorderless();
    static bool IsWireframe();
    static int GetMaxPointLights();
    static PointLight* GetPointLight(int _lightIndex);
    static std::vector<PointLight*> GetPointLights();
    
    RenderSettings(const RenderSettings&) = delete; // Singletons should not be assignable
    void operator=(const RenderSettings&) = delete; // Singletons should not be cloneable
};
