#include "GameObject.hpp"

namespace OK
{
    std::vector<GameObject*>* GameObject::GameObjects = nullptr;

    GameObject::GameObject(const std::string& name,
                            glm::vec3 pos,
                            glm::vec3 scl,
                            glm::quat rot)
    {
        if (GameObjects == nullptr)
        {
            GameObjects = new std::vector<GameObject*>();
        }
        m_name = name;
        m_trasform.position = pos;
        m_trasform.scale = scl;
        m_trasform.rotation = rot;
        GameObjects->push_back(this);
    }
    
    bool GameObject::hasComponentWithID(int componentID)
    {
        return std::find(m_components.begin(), m_components.end(), componentID) != m_components.end();
    }

    std::string GameObject::getName()
    { return m_name; }

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
        GFX_DEBUG("Added Component with ID: %d to GameObject with name %s and ID: %d. Now has %d Components.", componentID, m_name.data(), m_ID, m_components.size())
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