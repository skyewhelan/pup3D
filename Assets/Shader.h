// pup3D - puppy powered engine
// Shader.h
// Defines static functions for loading, compiling, and validating GLSL shaders
// Skye Whelan

#pragma once
#include <glew.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace Shader
{
    // Return the string contents of a file
    static std::string LoadFile(const char* _filePath)
    {
        std::ifstream File;
        std::stringstream Buffer;
        File.exceptions (std::ifstream::failbit | std::ifstream::badbit);
        
        try
        {
            File.open(_filePath);
            Buffer << File.rdbuf();
            File.close();
        }
        catch (std::ifstream::failure& err)
        {
            std::cout << "Failed to read file " << _filePath << ":\n" << err.what() << "\n";
        }
        
        return Buffer.str();
    }
    
    // Check if a shader was successfully compiled
    static bool ValidateShader(GLuint _shader, const char* _path)
    {
        int Success;
        char InfoLog[512];
        
        glGetShaderiv(_shader, GL_COMPILE_STATUS, &Success);
        if(!Success)
        {
            glGetShaderInfoLog(_shader, 512, NULL, InfoLog);
            std::cout << "Failed to compile shader "<< _shader << " at " << _path << ":\n" << InfoLog << "\n";
        }
        return Success;
    }
    
    // Check if a shader program was successfully compiled
    static bool ValidateProgram(GLuint _program)
    {
        int Success;
        char InfoLog[512];
        
        glGetProgramiv(_program, GL_LINK_STATUS, &Success);
        if(!Success)
        {
            glGetProgramInfoLog(_program, 512, NULL, InfoLog);
            std::cout << "Failed to validate shader program " << _program << ":\n" << InfoLog << "\n";
        }
        
        return Success;
    }
    
    // Compile a shader of the given type from a file at the given path
    static GLuint Compile(const char* _filePath, GLenum _type)
    {
        GLuint NewShader = glCreateShader(_type);
        std::string Source = LoadFile(_filePath);
        const char* ShaderCode = Source.c_str();
        
        glShaderSource(NewShader, 1, &ShaderCode, NULL);
        glCompileShader(NewShader);
        ValidateShader(NewShader, _filePath);
        return NewShader;
    }
    
    // Link any number of shaders together into a shader program
    static GLuint CreateProgram(std::vector<GLuint> _shaders)
    {
        GLuint NewProgram = glCreateProgram();
        
        for (GLuint Shader : _shaders)
        {
            glAttachShader(NewProgram, Shader);
        }
        
        glLinkProgram(NewProgram);
        ValidateProgram(NewProgram);
        return NewProgram;
    }
}
