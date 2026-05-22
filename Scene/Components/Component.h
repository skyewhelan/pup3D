#pragma once
#include <glew.h>
#include <glfw3.h>
#include <string>
#include <vector>
class Actor;
class Camera;

class Component
{
public:
    enum class Type : uint8_t
    {
        NONE,
        TRANSFORM,
        CAMERA,
        EYECAM,
        FREECAM,
        ORBITCAM,
        MESH,
        POINTLIGHT,
        DIRLIGHT,
        BOXCOLLIDER,
    };
protected:
    std::string m_Name;
    Type m_Type = Type::NONE;
    bool m_IsActive = true;
    Actor* m_OwningActor = nullptr;
    Component* m_Parent = nullptr;
    std::vector<Component*> m_Children;
    
public:
    
    Component();
    ~Component();
    
    virtual void Update(float _deltaTime);
    virtual void Render();
    virtual void SetActive(bool _active);
    
    void AttachTo(Actor* _actor, Component* _attachPoint = nullptr);
    void Detach();
    void AddChild(Component* _child);
    
    bool IsActive();
    Actor* GetOwningActor();
    Component* GetParent();
    std::vector<Component*> GetChildren();
    std::string GetName();
    Type GetType();
    
    static bool FindComponentsByName(std::string _name, Component* _root, std::vector<Component*>* _out);
    static bool FindComponentsByType(Type _type, Component* _root, std::vector<Component*>* _out);
};
