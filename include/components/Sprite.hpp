#pragma once
#include "components/core/FlatGraphics.hpp"

namespace OK
{

class Sprite : public FlatGraphics
{
protected:

    void prepareGraphics() override;
    void update(float deltaTime) override;
    void draw() override;

public:
    Sprite(
        Texture2D texture
    );

    Texture2D m_texture;
};

} // Namespace OK
