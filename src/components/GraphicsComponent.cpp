#include "components/GraphicsComponent.hpp"
#include "Scene.hpp"

namespace OK
{

    GraphicsComponent::GraphicsComponent() : Component(){ }

    void GraphicsComponent::onCreated()
    {
        Scene::currentScene->m_graphicsComponents.emplace_back(shared_from_this());
    }

} // Namespace OK