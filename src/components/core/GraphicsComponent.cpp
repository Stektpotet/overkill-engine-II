#include "components/core/GraphicsComponent.hpp"
#include "Scene.hpp"

namespace OK
{

    GraphicsComponent::GraphicsComponent() : Component(), m_vertexArray() { }

    glm::mat4 GraphicsComponent::modelViewMatrix()
    {
        return m_gameObject->m_transform.modelMatrix();
    }
    
    void GraphicsComponent::onCreated()
    {
        Scene::currentScene->m_graphicsComponents.emplace_back(shared_from_this());
    }

} // Namespace OK