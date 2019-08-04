#pragma once
#include "GameObject.hpp"
#include <type_traits>

template<typename TComponent, typename... Args>
std::shared_ptr<TComponent> OK::GameObject::addComponent(Args&&... ctorArgs)
{
    auto component = m_components.emplace_back(
        std::make_shared<TComponent>(this, m_components.size(), std::forward<Args>(ctorArgs)...)
    );
    component->onCreated();
    component->awake();

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
