#pragma once
#include "GameObject.hpp"
#include <type_traits>

template<typename TComponent, typename... Args>
std::shared_ptr<TComponent> OK::GameObject::addComponent(Args&&... ctorArgs)
{
    auto component = m_components.emplace_back(
        std::make_shared<TComponent>(std::forward<Args>(ctorArgs)...)
    );
    component->m_gameObject = this;
    component->m_ID = m_components.size() - 1;

    component->onCreated();
    component->awake();

    GFX_DEBUG(
        "Constructed Component {%s} with ID: %d with parent GameObject: %s", 
        typeid(component).name(), 
        component->m_ID, 
        this->getName().data()
    );
    return std::static_pointer_cast<TComponent>(component);
}

template<typename TComponent>
std::shared_ptr<TComponent> OK::GameObject::getComponent()
{
    for (const auto& c : m_components)
        if (auto component = std::dynamic_pointer_cast<TComponent>(c); component)
            return component;
    return nullptr;
    GFX_WARN("Found no component of type \"%s\"", typeid(TComponent).name());
}
