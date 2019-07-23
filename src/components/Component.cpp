#include "components/Component.hpp"

namespace OK
{

// Static functions:
    //std::shared_ptr<Component> Component::GetByID(int componentID)
    //{
    //    if (Components == nullptr)
    //    {
    //        return nullptr;
    //    }
    //    auto iterator = std::find_if(Components->begin(), Components->end(), [componentID](std::shared_ptr<Component> c){return c->m_ID == componentID;});
    //    int index = std::distance(Components->begin(), iterator);
    //    return Components->at(index);
    //}

    //void Component::Update(float deltaTime)
    //{
    //    if (Components == nullptr)
    //    {
    //        return;
    //    }
    //    //GFX_DEBUG("Updating all %d components->..", Components->size());
    //    for (int i = 0; i < Components->size(); i++)
    //    {
    //        Components->at(i)->update(deltaTime);
    //    }
    //}
    

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

}