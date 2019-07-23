#pragma once
#include <vector>
#include <algorithm>        // Find() in vector.
#include "GameObject.hpp" // include circle. But would like to have ref anyways :/
#include <gfx.h>
#include <memory> //smart pointers

namespace OK
{
    
class Component 
{
    friend class GameObject;
private:
    //static std::vector<std::shared_ptr<Component>>* Components;
    int m_ID;
protected:
    Component(GameObject* gameObject, int id);
    virtual void update(float deltaTime)=0;     // Has to be pure virtual.
    //virtual void draw()=0; 
public:
    GameObject* m_gameObject;
    //static std::shared_ptr<Component> GetByID(int componentID);     // Returns nullptr if ID doesn't exist.
    //static void Update(float deltaTime);
    //static void Draw();

    int getID();
    bool operator== (const int& otherID);
    bool operator== (const Component& otherComponent);
    bool operator== (const Component* otherComponent);
};

}