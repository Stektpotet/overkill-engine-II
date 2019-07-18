#include "components/Component.hpp"

namespace OK
{

    std::vector<Component*>* Component::Components = nullptr;


// Static functions:
    Component* Component::GetByID(int componentID)
    {
        auto iterator = std::find_if(Components->begin(), Components->end(), [componentID](Component * c){return c->m_ID == componentID;});
        int index = std::distance(Components->begin(), iterator);
        return Components->at(index);
    }

    void Component::Update(float deltaTime)
    {
        //GFX_DEBUG("Updating all %d components->..", Components->size());
        for (int i = 0; i < Components->size(); i++)
        {
            Components->at(i)->update(deltaTime);
        }
    }

// Non-static funcions:
    Component::Component(GameObject* gameObject)
    {
        if (Components == nullptr)
        {
            Components = new std::vector<Component*>();
        }
        m_ID = Components->size();
        m_gameObject = gameObject; 
        Components->push_back(this);
        GFX_DEBUG("Constructed Component with ID: %d with parent GameObject: %s", m_ID, gameObject->getName().data());
    }

    int Component::getID()
    { return m_ID; }


    bool Component::operator== (const int& otherID)
    { return m_ID == otherID; }

    bool Component::operator== (const Component& otherComponent)
    { return m_ID == otherComponent.m_ID; }

    bool Component::operator== (const Component* otherComponent)
    { return m_ID == otherComponent->m_ID; }

}