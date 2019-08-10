#pragma once

#include "components/SpriteAtlas.hpp"

namespace OK
{

class AnimatedSprite : public SpriteAtlas
{
private:
    int m_currentFrame;
    int m_maxFrames;
    float m_wait;           // The time to wait before switching again.
    bool m_reversed;        // Is the animation playing backwards?

protected:
    void update(float deltaTime) override;

public:
    AnimatedSprite(
        Texture2DArray texture,
        float duration = 2,
        int maxFrames = -1,     // -1 If using all slots in atlas.
        bool loop = true,
        bool reverseOnEnd = false,
        bool playing = true
    );

    bool m_playing;
    bool m_loop;
    bool m_reverseOnEnd;    // Rather or not the animation plays backwards once it reaches its end.
    float m_frameDuration;     // Time in between switching frames.

    void setAnimationDuration(float seconds);
    void reset(bool playing = true);            // Resets the animation to is first frame, resets any state, and starts playing if 'playing' param true.
};

} // Namespace OK