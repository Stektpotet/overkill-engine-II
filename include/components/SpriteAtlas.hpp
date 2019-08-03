#pragma once

#include "components/FlatGraphics.hpp"

namespace OK
{

class SpriteAtlas : public FlatGraphics
{
protected:

    void prepareGraphics() override;
    void update(float deltaTime) override;
    void configureShader(ShaderProgram shader) override;
    void draw() override;

public:
    SpriteAtlas(
        GameObject* gameObject,
        int id, 
        TextureAtlas atlas,
        int atlasIndex
    );

    int m_atlasIndex = -1;       // Minus one when not using an atlas.
    TextureAtlas m_atlas;
};

} // Namespace OK
