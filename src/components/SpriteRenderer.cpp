#include "components/SpriteRenderer.hpp"


namespace OK
{
    SpriteRenderer::SpriteRenderer(
        GameObject* gameObject,
        int id, 
        Texture2D texture
        ) : FlatGraphics(gameObject, id), m_texture{texture}
        {}
    
    void SpriteRenderer::update(float deltaTime)
    {
        m_rotation += deltaTime*2;
    }

    void SpriteRenderer::draw()
    {        
        m_texture.bind();
        FlatGraphics::draw();
        m_texture.unbind();
    }
    
} // Namespace OK
