#include "components/core/Component.hpp"

namespace OK
{

// Non-static funcions:
    //Component::Component()
    //{
    //}

    int Component::getID()
    { return m_ID; }

    bool Component::operator== (const int& otherID)
    { return m_ID == otherID; }

    bool Component::operator== (const Component& otherComponent)
    { return m_ID == otherComponent.m_ID; }

    bool Component::operator== (const Component* otherComponent)
    { return m_ID == otherComponent->m_ID; }

} // Namespace OK
