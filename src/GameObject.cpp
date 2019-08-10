#include "GameObject.hpp"

namespace OK
{
    GameObject::GameObject(
        const std::string& name,
        glm::vec3 pos,
        glm::vec3 scl,
        glm::quat rot
    ) : m_name{ name },
        m_transform { pos, scl, rot },
        m_components{}
    {
    }
    
    void GameObject::update(float deltaTime)
    {
        for (auto& c : m_components)
            c->update(deltaTime);
    }
} // Namespace OK.