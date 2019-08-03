#pragma once
#include <vector>
#include <algorithm>        // Find() in vector.
#include "GameObject.hpp" // include circle. But would like to have ref anyways :/
#include <gfx.h>
#include <memory> //smart pointers

namespace OK
{
class GameObject;
class Component 
{
    //struct Hash
    //{
    //    std::size_t operator()(Component const& c) const noexcept
    //    {
    //        std::size_t h1 = std::hash<int>{}(c.m_ID);
    //        std::size_t h2 = std::hash<int>{}(c.m_gameObject->getID());
    //        std::size_t h3 = std::hash<std::string>{}(c.m_gameObject->getName());
    //        //TODO: https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
    //        return (h1 ^ (h2 << 1)) ^ (h3 << 1); // or use boost::hash_combine (see Discussion)
    //    }
    //};


    friend class GameObject;
private:
    int m_ID;
protected:
    Component(GameObject* gameObject, int id);
    virtual void update(float deltaTime) {}     // Has to be pure virtual.
    inline virtual void draw() {}
public:
    GameObject* m_gameObject;

    int getID();
    bool operator== (const int& otherID);
    bool operator== (const Component& otherComponent);
    bool operator== (const Component* otherComponent);
};

}