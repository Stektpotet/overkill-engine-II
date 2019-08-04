#include "components/AnimatedSprite.hpp"

extern glm::vec2 windowSize;

namespace OK
{
AnimatedSprite::AnimatedSprite(
    GameObject* gameObject,
    int id,
    TextureAtlas texture
    ) : SpriteAtlas(gameObject, id, texture)
    {}


    //
    // OpenGL setup done in FlatGraphics.
    //

    void AnimatedSprite::update(float deltaTime)
    {
        //m_rotation += deltaTime * 0.25f;
        //m_atlasIndex = int(m_rotation*90)%(m_atlas.getDepth()-1);
    }

    //
    // Drawing done by GraphicsComponent.
    //
}
