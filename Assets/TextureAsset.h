// pup3D - puppy powered engine
// TextureAsset.h
// Creates and stores a reference to an opengl texture
// Skye Whelan

#pragma once
#include <glew.h>
#include <glfw3.h>

class TextureAsset
{
    GLuint m_ID;
public:
    TextureAsset(char const* _filePath);
    
    GLuint GetID();
};
