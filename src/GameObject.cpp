#include "GameObject.hpp"

namespace OK
{
    std::vector<GameObject*>* GameObject::GameObjects = nullptr;

    GameObject::GameObject(
        const std::string& name,
        glm::vec3 pos,
        glm::vec3 scl,
        glm::quat rot
    ) : m_name{ name },
        m_transform { pos, scl, rot},
        m_components{}
    {
        if (GameObjects == nullptr)
        {
            GameObjects = new std::vector<GameObject*>();
        }
        GameObjects->push_back(this);
    }
}