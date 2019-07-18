#pragma once
#include <vector>
#include <algorithm>        // Find() in vector.
#include "GameObject.hpp" // include circle. But would like to have ref anyways :/
#include <gfx.h>

namespace OK
{
    
class Component
{
private:
    static std::vector<Component*>* Components;
    int m_ID;
protected:
    virtual void update(float deltaTime)=0;     // Has to be pure virtual.
    virtual void draw()=0; 
public:
    GameObject* m_gameObject;
    static Component* GetByID(int componentID);     // Returns nullptr if ID doesn't exist.
    static void Update(float deltaTime);

    Component(GameObject* gameObject);
    int getID();
    bool operator== (const int& otherID);
    bool operator== (const Component& otherComponent);
    bool operator== (const Component* otherComponent);
};

}