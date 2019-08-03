#pragma once

#include "components/FlatGraphics.hpp"

namespace OK
{

class SpriteRenderer : public FlatGraphics
{
protected:
    void update(float deltaTime) override;
    void draw() override;

public:
    SpriteRenderer(
        GameObject* gameObject,
        int id, 
        Texture2D texture
    );

    Texture2D m_texture;

};

} // Namespace OK
