#include "components/AnimatedSprite.hpp"

extern glm::vec2 windowSize;

namespace OK
{
AnimatedSprite::AnimatedSprite(
    GameObject* gameObject,
    int id,
    TextureAtlas texture,
    float duration,
    int maxFrames,
    bool loop,
    bool reverseOnEnd,
    bool playing
    ) : SpriteAtlas(gameObject, id, texture),
    m_maxFrames{maxFrames},
    m_loop{loop},
    m_reverseOnEnd(reverseOnEnd),
    m_playing{playing}
    {
        if (m_maxFrames <= 0)
            m_maxFrames = m_atlas.getDepth();
            
        setAnimationDuration(duration);
        m_currentFrame = 0;
        m_wait = m_frameDuration;
        m_reversed = false;
    }


    //
    // OpenGL setup done in FlatGraphics.
    //

    void AnimatedSprite::update(float deltaTime)
    {
        if (m_playing)      m_wait -= deltaTime;
        if (m_wait <= 0)    m_wait = m_frameDuration;
        else                return;

        m_currentFrame += (m_reversed)? -1 : 1;

        if (m_currentFrame == m_maxFrames)
        {
            if (m_loop)
                m_currentFrame = 0;
            else
                m_playing = false;
        }

        if (m_reverseOnEnd && m_currentFrame == m_maxFrames-1)
        {
                m_reversed = true;
        }

        if (m_reversed && m_currentFrame == 0)
        {
            m_reversed = false;
            if (!m_loop)
                m_playing = false;
        }

        m_atlasIndex = m_currentFrame;
    }

    void AnimatedSprite::setAnimationDuration(float seconds)
    {   m_frameDuration = seconds / (float)m_maxFrames; }

    void AnimatedSprite::reset(bool playing)
    {
        m_currentFrame = 0;
        m_wait = m_frameDuration;
        m_reversed = false;
        m_playing = playing;
    }


    //
    // Drawing done by GraphicsComponent.
    //
} // Namespace OK