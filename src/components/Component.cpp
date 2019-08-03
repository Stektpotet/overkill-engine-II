#include "components/Component.hpp"

namespace OK
{

// Non-static funcions:
    Component::Component(GameObject* gameObject, int id)
    {
        m_gameObject = gameObject;
        GFX_DEBUG("Constructed Component {%s} with ID: %d with parent GameObject: %s", typeid(this).name(), m_ID, gameObject->getName().data());
    }

    int Component::getID()
    { return m_ID; }

    bool Component::operator== (const int& otherID)
    { return m_ID == otherID; }

    bool Component::operator== (const Component& otherComponent)
    { return m_ID == otherComponent.m_ID; }

    bool Component::operator== (const Component* otherComponent)
    { return m_ID == otherComponent->m_ID; }

} // Namespace OK
