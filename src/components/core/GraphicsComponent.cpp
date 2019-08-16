#include "components/core/GraphicsComponent.hpp"

namespace OK
{

inline void GraphicsComponent::prepareGraphics() {}

inline glm::mat4 GraphicsComponent::modelToWorldMatrix() 
{ 
    return m_gameObject->m_transform.modelMatrix(); 
}

inline void GraphicsComponent::onCreated()
{
    Scene::currentScene->m_graphicsComponents.emplace_back(shared_from_this());
}
GraphicsComponent::GraphicsComponent() : Component(), m_vertexArray()
{}

}