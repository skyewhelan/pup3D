#pragma once
#include <glew.h>
#include <glfw3.h>

class Texture
{
    GLuint m_ID;
public:
    Texture(char const* _filePath);
    
    GLuint GetID();
};
