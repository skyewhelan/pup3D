// pup3D - puppy powered engine
// TextureAsset.cpp
// 
// Skye Whelan

#include "TextureAsset.h"
#define STB_IMAGE_IMPLEMENTATION
#include <iostream>
#include <ostream>
#include <stb_image.h>

TextureAsset::TextureAsset(const char* _filePath)
    {
    glGenTextures(1, &m_ID);
    glBindTexture(GL_TEXTURE_2D, m_ID);
    
    // Texture wrapping
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // LOD; Mipmaps and anisotropic filtering
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.0f);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 8.0f);
    
    int Width, Height, Channels;
    unsigned char* Data = stbi_load(_filePath, &Width, &Height, &Channels, 0);
    
    if (Data != nullptr)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
        //glTexImage2D(GL_TEXTURE_2D, 0, GL_SRGB_ALPHA, Width, Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, Data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture " << m_ID << " at " << _filePath << "\n";
    }
    
    stbi_image_free(Data);
}

GLuint TextureAsset::GetID()
{
    return m_ID;
}
