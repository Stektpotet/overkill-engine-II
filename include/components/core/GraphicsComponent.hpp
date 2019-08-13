#pragma once
#include "components/core/Component.hpp"

#include "graphics_internal/VertexArray.hpp"
#include "graphics_internal/VertexBuffer.hpp"
#include "graphics_internal/VertexLayout.hpp"
#include "graphics_internal/IndexBuffer.hpp"
#include "graphics_internal/ShaderProgram.hpp"
#include "graphics_internal/Texture.hpp"

#include "../../model/Mesh.hpp"

namespace OK
{
class GameObject;
// TODO: Revert changes - put functionality back into a .cpp -file
class GraphicsComponent : public Component, public std::enable_shared_from_this<GraphicsComponent>
{
    friend class Scene;
protected:
    VertexArray m_vertexArray;

    inline virtual void prepareGraphics() {}
    inline virtual glm::mat4 modelToWorldMatrix(){ return m_gameObject->m_transform.modelMatrix(); }

    void onCreated() override
    {
        Scene::currentScene->m_graphicsComponents.emplace_back(shared_from_this());
    }
    GraphicsComponent() : Component(), m_vertexArray(){}
    virtual void draw() = 0;

};

} // Namespace OK