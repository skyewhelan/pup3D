// pup3D - puppy powered engine
// TestScene.cpp
// 
// Skye Whelan

#include "TestScene.h"
#include "../Input/Input.h"
#include "Misc/FreeCam.h"

TestScene::TestScene()
{
    GenerateAssets();
    ConstructScene();
}

void TestScene::GenerateAssets()
{
    Scene::GenerateAssets();
    
    // Meshes
    AddMesh("Cube", new Mesh(Shape::Cube()));
    
    // Textures
    AddTexture("BrickWall", new Texture("Resources/Textures/wall.jpg"));
    
    // Shaders
    GLuint Vert = Shader::Compile("Resources/Shaders/3DBasic.vert", GL_VERTEX_SHADER);
    GLuint Frag = Shader::Compile("Resources/Shaders/BasicTexture.frag", GL_FRAGMENT_SHADER);
    AddShaderProgram("2DBasic", Shader::CreateProgram({Vert, Frag}));
}

void TestScene::ConstructScene()
{
    Scene::ConstructScene();
    
    m_MainCamera = new FreeCam();
    m_MainCamera->SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
    
    // Actors
    AddActor("Wall2D", new Actor(
        GetMesh("Cube"),
        GetTexture("BrickWall"),
        GetShaderProgram("2DBasic")));
    
    GetActor("Wall2D")->Rotate({25.0f, 45.0f, 0.0f});
    
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
        Actor* Box = AddActor("Wall" + std::to_string(i), new Actor(
            GetMesh("Cube"),
            GetTexture("BrickWall"),
            GetShaderProgram("2DBasic")));
        
        Box->SetPosition(cubePositions[i]);
    }
}

void TestScene::Update(float _deltaTime)
{
    Scene::Update(_deltaTime);
    
    GetActor("Wall2D")->Rotate({0.0f, 250.0f * _deltaTime, 0.0f});
    //m_MainCamera->SetPosition({sin(glfwGetTime()) * 10, 0.0f, cos(glfwGetTime()) * 10});
}

void TestScene::KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods)
{
    InputReceiver::KeyCallback(_window, _key, _scancode, _action, _mods);
    
}
