#pragma once

#include "components/SpriteAtlas.hpp"

namespace OK
{

class AnimatedSprite : public SpriteAtlas
{
protected:
    void update(float deltaTime) override;

public:
    AnimatedSprite(
        GameObject* gameObject,
        int id, 
        TextureAtlas texture
    );
};

}
