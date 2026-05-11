#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <ostream>
#include <stb_image.h>

Texture::Texture(const char* _filePath)
    {
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int Width, Height, Channels;
    unsigned char* Data = stbi_load(_filePath, &Width, &Height, &Channels, 0);
    
    if (Data != nullptr)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture " << m_ID << " at " << _filePath << "\n";
    }
    
    stbi_image_free(Data);
}

GLuint Texture::GetID()
{
    return m_ID;
}
