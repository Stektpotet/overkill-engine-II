#pragma once
#include "components/core/GraphicsComponent.hpp"

#include "graphics_internal/VertexArray.hpp"
#include "graphics_internal/VertexBuffer.hpp"
#include "graphics_internal/VertexLayout.hpp"
#include "graphics_internal/IndexBuffer.hpp"
#include "graphics_internal/ShaderProgram.hpp"
#include "graphics_internal/Texture.hpp"

#include "../../model/Mesh.hpp"

namespace OK
{
template<typename DrawableType>
class Renderer : public GraphicsComponent
{
protected:
    DrawableType* m_drawable;
    std::shared_ptr<Material> m_material;

public:
    Renderer(DrawableType drawable) : m_drawable{ &drawable }, GraphicsComponent()
	{ 
		drawable.bind(); //bind during creation to allow rendertargets to also bind into the correct state of the context
        GFX_DEBUG("Bound drawable")
	}
    
    Renderer() : GraphicsComponent{}
    {}
};

} // Namespace OK