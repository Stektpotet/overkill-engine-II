#include "GameObject.hpp"
#include <type_traits>

template<typename TComponent, typename... Args>
std::shared_ptr<TComponent> OK::GameObject::addComponent(Args&&... ctorArgs)
{
    //TODO: try to make this even more in-place
    auto newComponent = std::make_shared<TComponent>(this, std::forward<Args>(ctorArgs)...); 
    Component::Components->push_back(newComponent);

    if (hasComponentWithID(newComponent->m_ID))
    {
        GFX_ERROR("Cannot add a duplicate Component to a GameObject(%s)", m_name.data());
    }
    m_components.push_back(newComponent->m_ID);
    GFX_DEBUG("Added Component with ID: %d to GameObject with name %s and ID: %d. Now has %d Components.", newComponent->m_ID, m_name.data(), m_ID, m_components.size())
    return newComponent;
}

template<typename TComponent>
std::shared_ptr<TComponent> OK::GameObject::getComponent()
{
    for (auto& c : (*Component::Components))
        for (const auto& c_id : m_components)
            if (c_id == c->m_ID)
                if (auto component = std::dynamic_pointer_cast<TComponent>(c); component)
                    return component;

    GFX_WARN("Found no component of type \"%s\"", typeid(TComponent).name());
}