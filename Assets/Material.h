// pup3D - puppy powered engine
// Material.h
// Defines parameters for how the surface of a mesh is lit and rendered
// Skye Whelan

#pragma once
#include <vec3.hpp>
#include <glew.h>
#include <glm.hpp>
#include <map>
#include <string>
#include <vec4.hpp>

class TextureAsset;

class Material
{
private:
    TextureAsset* m_Texture;
    GLuint m_ShaderProgram;
    bool m_IsLit;
    
    std::map<std::string, GLint> m_ParamsInt = {};
    std::map<std::string, GLfloat> m_ParamsFloat = {};
    std::map<std::string, glm::vec3> m_ParamsVec3 = {};
    std::map<std::string, glm::vec4> m_ParamsVec4 = {};
    std::map<std::string, glm::mat4> m_ParamsMat4 = {};
    
    
public:
    Material(TextureAsset* _texture, GLuint _shaderProgram, bool _lit);
    
    void SetUniforms();
    
    TextureAsset* GetTexture();
    GLuint GetShaderProgram();
    bool IsLit();
    
    void AddParamInt(std::string _name, GLint _value);
    void AddParamFloat(std::string _name, GLfloat _value);
    void AddParamVec3(std::string _name, glm::vec3 _value);
    void AddParamVec4(std::string _name, glm::vec4 _value);
    void AddParamMat4(std::string _name, glm::mat4 _value);
    
    void SetParamInt(std::string _name, GLint _value);
    void SetParamFloat(std::string _name, GLfloat _value);
    void SetParamVec3(std::string _name, glm::vec3 _value);
    void SetParamVec4(std::string _name, glm::vec4 _value);
    void SetParamMat4(std::string _name, glm::mat4 _value);
    
    GLuint GetParamInt(std::string _name);
    GLfloat GetParamFloat(std::string _name);
    glm::vec3 GetParamVec3(std::string _name);
    glm::vec4 GetParamVec4(std::string _name);
    glm::mat4 GetParamMat4(std::string _name);
};