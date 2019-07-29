#pragma once
#include <string>
#include <vector>
#include <algorithm>        // Find() in vector.
#include "Transform.hpp"
#include "components/Component.hpp"
#include <gfx.h>
#include <memory>

namespace OK
{
class Component;
class GameObject
{
private:
    static std::vector<GameObject*>* GameObjects; //TODO: Move to scene layer or whateverthefuck we'll call them
    
    int m_ID;
    //std::vector<int> m_components;
    std::string m_name;
    std::vector<std::shared_ptr<Component>> m_components;
public:
    Transform m_transform;
    GameObject(const std::string& name = "GameObject", 
               glm::vec3 pos = glm::vec3{ 0, 0, 0 },
               glm::vec3 scl = glm::vec3{ 1, 1, 1 },
               glm::quat rot = glm::quat{ 0, 0, 0, 1 });

    inline const std::string& getName() { return m_name; }
    inline const int getID() { return m_ID; }
    
    void update(float deltaTime);

    ///<summary>
    /// Adds a Component of the specified type to the GameObject. 
    /// Allows for in-place construction by taking TComponent's constructor arguments.
    /// Can fail if it already has the component or the component already has a GameObject reference.
    /// </summary>
    template<typename TComponent, typename... Args>
    std::shared_ptr<TComponent> addComponent(Args&&... ctorArgs);

    template<typename TComponent>
    std::shared_ptr<TComponent> getComponent();

    //bool removeComponent(int componentID);      // Removes the component so it is no longer assiciated with this GameObject.
                                                // NB! Does not destroy the component.
};
#include "GameObject.tpp" //Template implementations
}