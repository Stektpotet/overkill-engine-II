#pragma once

#include "components/SpriteAtlas.hpp"

namespace OK
{

class TextInstanced : public FlatGraphics
{
private:
    const char* c_fontAtlas = "assets/textures/ascii.png";
    const uint16_t c_atlasDivisions = 16;
    const char* m_text;

    float m_spacing = 0.5f;

    glm::vec4 m_color   = glm::vec4(1, 1, 1, 1);

    TextureAtlas m_asciiMap;

protected:
    void draw() override;
    void prepareGraphics() override;

public:
    TextInstanced(GameObject* gameObject, int id, const char* text, const char* fontAtlas = "assets/textures/ascii.png");


    inline size_t textLength() { return std::char_traits<char>::length(m_text); }
    void setText(const char* newText);
};

} // Namespace OK.