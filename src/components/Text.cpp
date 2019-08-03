#include "components/Text.hpp"

namespace OK
{

Text::Text(GameObject* gameObject, int id, const std::string text, bool rainbow) : Component(gameObject, id)
{
    m_rainbow = rainbow;
    m_text = text;

    GFX_DEBUG("Building Text for the string '%s'(length %d)", text.data(), text.length());

    // Load texture:
    TextureAtlas blockTextureAtlas;
	int err = loadTextureAtlas(c_characterAtlas.data(), 16, &blockTextureAtlas);

    // Construct a sprite for each character:
    for (int i = 0; i < text.length(); i++)
    {
        GFX_DEBUG("Creating sprite for the char '%c' with int decimal value %d.", text[i], text[i]);
        m_characters.push_back(std::make_shared<SpriteAtlas>(
                                    gameObject,gameObject->getID(),
                                    blockTextureAtlas, 
                                    text[i]%(c_atlasDivisions * c_atlasDivisions)
                                    )
                                );
        std::shared_ptr<SpriteAtlas> chr = std::static_pointer_cast<SpriteAtlas>(m_characters.back());
        chr->m_offset = glm::vec2(i * (m_spacing * m_charSize), 0);
        chr->m_rotation = m_rotation;
    }
}

//Getters:
std::string Text::getText()
{    return m_text; }

int Text::getLenght()
{    return m_text.length(); }

float Text::getRotation()
{   return m_rotation;  }

float Text::getSize()
{    return m_charSize; }

glm::vec4 Text::getColor()
{    return m_color; }


//Setters:
void Text::setText(const std::string)
{

}
void Text::setRotation(float rotation)
{
    m_rotation = rotation;
    for(std::shared_ptr<SpriteAtlas> s : m_characters)
    {
        s->m_rotation = rotation;
    }
}
void Text::setSize(float size)
{
    for(std::shared_ptr<SpriteAtlas> s : m_characters)
    {
        s->m_size = {size, size};
    }
}
void Text::setColor(glm::vec4 color)
{
    for(std::shared_ptr<SpriteAtlas> s : m_characters)
    {
        s->m_color = color;
    }
}

// GameLoop functions:
void Text::update(float deltatTime)
{

}

} // Namespace OK.
