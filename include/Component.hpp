#pragma once
#include <vector>
#include <algorithm>        // Find() in vector.
//#include "GameObject.hpp" // include circle. But would like to have ref anyways :/


namespace OK
{
    
class Component
{
private:
    static std::vector<Component*> Components;
    int m_ID;
public:
    //GameObject* gameObject; // include circle. But would like to have ref anyways :/
    Component* GetByID(int componentID);     // Returns nullptr if ID doesn't exist.
    Component();
    
    bool operator== (const int& otherID);
    bool operator== (const Component& otherComponent);
    bool operator== (const Component* otherComponent);

    virtual void update(float deltaTime)=0;
    virtual void draw()=0; 
};

}