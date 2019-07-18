#include "GameObject.hpp"

namespace OK
{

    GameObject::GameObject( std::string name,
                            glm::vec3 pos,
                            glm::vec3 scl,
                            glm::quat rot)
    {
        m_name = name;
        m_trasform.position = pos;
        m_trasform.scale = scl;
        m_trasform.rotation = rot;
    }

    GameObject::GameObject( std::string name,
                            Transform trans)
    {
        m_name = name;
        m_trasform = trans;
    }
    
    bool GameObject::hasComponentWithID(int componentID)
    {
        return std::find(m_components.begin(), m_components.end(), componentID) != m_components.end();
    }

    bool GameObject::addComponent(int componentID)
    {
        if (hasComponentWithID(componentID))
        {
            GFX_WARN("Cannot add a duplicate Component to a GameObject(%s)", m_name.data());
            return false;
        }

        // if (Component::GetByID(componentID)->gameObject != nullptr)
        // {
        //     GFX_WARN("Cannot add an already in-use Component to a GameObject(%s). Only one GameObject per Component.", m_name.data());
        //     return false;
        // }

        //Component::GetByID(componentID)->gameObject == this;
        m_components.push_back(componentID);
        return true;
    }

    bool GameObject::removeComponent(int componentID)
    {
        if (!hasComponentWithID(componentID))
        {
            GFX_WARN("Cannot remove Component, Component ID not found.");
            return false;
        }

        //Component::GetByID(componentID)->gameObject = nullptr;
        std::remove(m_components.begin(), m_components.end(), componentID);

        return true;
    }
    
}