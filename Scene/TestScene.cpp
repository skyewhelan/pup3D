// pup3D - puppy powered engine
// TestScene.cpp
// 
// Skye Whelan

#include "TestScene.h"
#include "../Resources/Shape.h"
#include "Components/Cameras/FreeCam.h"
#include "Components/Cameras/OrbitCam.h"
#include "../Assets/Shader.h"
#include "../Core/RenderSettings.h"
#include "Components/MeshComponent.h"
#include "Components/PointLight.h"

TestScene::TestScene()
{
    GenerateAssets();
    ConstructScene();
}

void TestScene::GenerateAssets()
{
    Scene::GenerateAssets();
        
    // Meshes
    AddMesh("Cube", new MeshAsset(Shape::Cube()));
    AddMesh("Sphere", new MeshAsset(Shape::Sphere(0.5, 24)));
    
    // Textures
    AddTexture("BrickWall", new TextureAsset("Resources/Textures/test.png"));
    
    // Shaders
    GLuint Vert = Shader::Compile("Resources/Shaders/3DNormals.vert", GL_VERTEX_SHADER);
    GLuint Frag = Shader::Compile("Resources/Shaders/BlinnPhong.frag", GL_FRAGMENT_SHADER);
    AddShaderProgram("BlinnPhong", Shader::CreateProgram({Vert, Frag}));
    
    Frag = Shader::Compile("Resources/Shaders/UnlitColor.frag", GL_FRAGMENT_SHADER);
    AddShaderProgram("UnlitColor", Shader::CreateProgram({Vert, Frag}));
    
    Frag = Shader::Compile("Resources/Shaders/UnlitTexture.frag", GL_FRAGMENT_SHADER);
    AddShaderProgram("UnlitTexture", Shader::CreateProgram({Vert, Frag}));
    
    AddMaterial("TestMat", new Material(GetTexture("BrickWall"), GetShaderProgram("BlinnPhong"), true));
    Material* Blue = AddMaterial("UnlitColor", new Material(nullptr, GetShaderProgram("UnlitColor"), false));
    AddMaterial("UnlitTexture", new Material(GetTexture("BrickWall"), GetShaderProgram("UnlitTexture"), false));
    
    Material* Green = AddMaterial("Green", new Material(*Blue));
    Green->SetParamVec4("Albedo", {0.0f, 1.0f, 0.0f, 1.0f});
    
    GetMaterial("UnlitColor")->SetParamVec4("Albedo", {0.3f, 0.0f, 1.0f, 1.0f});
}

void TestScene::ConstructScene()
{
    Scene::ConstructScene(); 
    
    m_Skybox = new Skybox("Resources/Textures/Skybox/blink/");
    
    m_FreeCam = new FreeCam();
    m_FreeCam->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    m_OrbitCam = new OrbitCam({}, 1.0f, 5.0f);
    m_EyeCam = new EyeCam();
    m_EyeCam->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    
    m_MainCamera = m_FreeCam;
    RS::SetRenderCamera(m_MainCamera);
    
    // Terrain
    Terrain* Land = AddTerrain("Terrain", new Terrain("heightmap.save"));
    Land->SetPosition({0.0f, -10.0f, 0.0f});
    
    // Actors
    Actor* MainBox = AddActor("MainBox", new Actor());
    MainBox->AttachComponent(new MeshComponent(GetMesh("Cube"), GetMaterial("TestMat")));
    MainBox->SetRotation(MainBox->GetRotation() + glm::vec3(25.0f, 45.0f, 0.0f));
    
    Actor* LightActor = AddActor("Light", new Actor());
    LightActor->AttachComponent(new PointLight({0.3f, 0.0f, 1.0f}, 2.0f));
    LightActor->AttachComponent(new MeshComponent(GetMesh("Sphere"), GetMaterial("UnlitColor")));
    LightActor->SetPosition({5.0f, 5.0f, -5.0f});
    
    Actor* OtherLightActor = AddActor("OtherLight", new Actor());
    OtherLightActor->AttachComponent(new PointLight({0.0f, 1.0f, 0.0f}, 2.0f));
    OtherLightActor->AttachComponent(new MeshComponent(GetMesh("Sphere"), GetMaterial("Green")));
    OtherLightActor->SetPosition({-5.0f, 5.0f, -5.0f});
    
    glm::vec3 cubePositions[] = {
        glm::vec3( 2.0f,  5.0f, -15.0f),
        glm::vec3(-1.5f, -2.2f, -2.5f),
        glm::vec3(-3.8f, -2.0f, -12.3f),
        glm::vec3( 2.4f, -0.4f, -3.5f),
        glm::vec3(-1.7f,  3.0f, -7.5f),
        glm::vec3( 1.3f, -2.0f, -2.5f),
        glm::vec3( 1.5f,  2.0f, -2.5f),
        glm::vec3( 1.5f,  0.2f, -1.5f),
        glm::vec3(-1.3f,  1.0f, -1.5f)
    };
    
    for (int i = 0; i < 9; i++)
    {
        Actor* Box = AddActor("Box" + std::to_string(i), new Actor());
        Box->AttachComponent(new MeshComponent(GetMesh("Sphere"), GetMaterial("TestMat")));
        
        Box->SetPosition(cubePositions[i]);
    }
}

void TestScene::Update(float _deltaTime)
{
    Scene::Update(_deltaTime);
    Actor* MainBox = GetActor("MainBox");
    MainBox->SetRotation(MainBox->GetRotation() + glm::vec3(0.0f, 250.0f * _deltaTime, 0.0f));
}

void TestScene::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    InputReceiver::KeyCallback(_window, _key, _scancode, _action, _mods);
    
    if (_key == GLFW_KEY_TAB && _action == GLFW_PRESS)
    {
        if (m_MainCamera == m_FreeCam)
        {
            m_MainCamera = m_OrbitCam;
        }
        else
        {
            m_MainCamera = m_FreeCam;
        }
        
        RS::SetRenderCamera(m_MainCamera);
    }
    if (_key == GLFW_KEY_P && _action == GLFW_PRESS)
    {   
        GLuint Basic = GetShaderProgram("3DBasic");
        GLuint Affine = GetShaderProgram("3DAffine");
        
        for (auto EachActor : m_Actors)
        {
            std::vector<Component*> Meshes = {};
            Component::FindComponentsByType(Component::Type::MESH, EachActor.second->GetRoot(), &Meshes);
            if (!Meshes.empty())
            {
                MeshComponent* Mesh = dynamic_cast<MeshComponent*>(Meshes.at(0));
                if (Mesh != nullptr)
                {
                    if (Mesh->GetShaderProgram() == Basic)
                    {
                        Mesh->SetShaderProgram(Affine);
                    }
                    else
                    {
                        Mesh->SetShaderProgram(Basic);
                    }
                }
            }
        }
    }
}
