#pragma once

#include "components/SpriteAtlas.hpp"

namespace OK
{

class Text : public Component
{
private:
    const std::string c_characterAtlas = "assets/textures/ascii.png";
    const uint16_t c_atlasDivisions = 16;

    std::string m_text;
    std::vector<std::shared_ptr<SpriteAtlas>> m_characters;
    float m_charSize = 50;
    float m_rotation = 0;
    float m_spacing = 0.5f;

    glm::vec4 m_color   = glm::vec4(1, 1, 1, 1);

protected:
    void update(float deltaTime) override;

public:
    Text(GameObject* gameObject, int id, const std::string text, bool rainbow = false);

    bool m_rainbow;
    float m_shake = 0;
    
    std::string getText();
    int getLenght();
    float getRotation();
    float getSize();
    glm::vec4 getColor();

    void setText(const std::string);
    void setRotation(float size);
    void setSize(float size);
    void setColor(glm::vec4 color);
};

} // Namespace OK.