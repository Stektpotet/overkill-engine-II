#pragma once
#include <glm/glm.hpp>
#include "components/core/Component.hpp"

#include "graphics_internal/VertexArray.hpp"
#include "graphics_internal/VertexBuffer.hpp"
#include "graphics_internal/VertexLayout.hpp"
#include "graphics_internal/IndexBuffer.hpp"
#include "graphics_internal/ShaderProgram.hpp"
#include "graphics_internal/Texture.hpp"

#include "../../model/Mesh.hpp"

#include "Scene.hpp"

namespace OK
{
class GameObject;
class GraphicsComponent : public Component, public std::enable_shared_from_this<GraphicsComponent>
{
    friend class Scene;
protected:
    VertexArray m_vertexArray;
    
    inline virtual void prepareGraphics();
    inline virtual glm::mat4 modelToWorldMatrix();
    inline void onCreated() override;

    GraphicsComponent();
    virtual void draw() = 0;

};

} // Namespace OK