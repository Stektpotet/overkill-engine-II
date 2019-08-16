#pragma once
#include <glm/glm.hpp>
#include <string>

#include "components/SpriteRenderer.hpp"

namespace OK
{

class TextInstanced : public SpriteRenderer<Texture2DArray>
{
private:
    const char* m_text;

    float m_spacing = 0.5f;

protected:
    void draw() override;
    void prepareGraphics() override;

public:
    TextInstanced(const char* text, uint16_t dimensionWidth = 16, uint16_t dimensionHeight = 16, const char* fontAtlas = "assets/textures/ascii.png");


    inline size_t textLength() { return std::char_traits<char>::length(m_text); }
    void setText(const char* newText);
    glm::vec4 m_color   = glm::vec4(1, 1, 1, 1);
};

} // Namespace OK.