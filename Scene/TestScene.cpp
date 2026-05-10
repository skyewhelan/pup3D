// pup3D - puppy powered engine
// TestScene.cpp
// 
// Skye Whelan

#include "TestScene.h"

TestScene::TestScene()
{
    GenerateAssets();
    ConstructScene();
}

void TestScene::GenerateAssets()
{
    Scene::GenerateAssets();
    
    // Meshes
    AddMesh("Quad", new Mesh(Shape::Quad()));
    
    // Shaders
    GLuint Vert = Shader::Compile("Resources/Shaders/2Dbasic.vert", GL_VERTEX_SHADER);
    GLuint Frag = Shader::Compile("Resources/Shaders/2Dbasic.frag", GL_FRAGMENT_SHADER);
    AddShaderProgram("2DBasic", Shader::CreateProgram({Vert, Frag}));
}

void TestScene::ConstructScene()
{
    Scene::ConstructScene();
    
    // Actors
    AddActor("BlueQuad", new Actor(GetMesh("Quad"), GetShaderProgram("2DBasic")));
}
