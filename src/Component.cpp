#include "Component.hpp"

namespace OK
{

    std::vector<Component*> Component::Components = std::vector<Component*>();

    Component::Component()
    {
        m_ID = Components.size();
        //gameObject = nullptr; // include circle. But would like to have ref anyways :/
        Components.push_back(this);
    }

    Component* Component::GetByID(int componentID)
    {
        auto iterator = std::find_if(Components.begin(), Components.end(), [componentID](Component * c){return c->m_ID == componentID;});
        int index = std::distance(Components.begin(), iterator);
        return Components.at(index);
    }

    bool Component::operator== (const int& otherID)
    { return m_ID == otherID; }

    bool Component::operator== (const Component& otherComponent)
    { return m_ID == otherComponent.m_ID; }

    bool Component::operator== (const Component* otherComponent)
    { return m_ID == otherComponent->m_ID; }

}