#pragma once

// #include "components/SpriteAtlas.hpp"

// namespace OK
// {

// class Text : public Component
// {
// private:
//     const std::string c_characterAtlas = "assets/textures/ascii.png";
//     const __uint16_t c_atlasDivisions = 16;

//     std::string m_text;
//     std::vector<std::shared_ptr<SpriteAtlas>> m_characters;
//     float m_charSize;
//     glm::vec4 m_color   = glm::vec4(1, 1, 1, 1);

// protected:
//     void update(float deltaTime) override;

// public:
//     Text(GameObject* gameObject, int id, const std::string text, bool rainbow = false);

//     bool m_rainbow;
//     float m_shake = 0;
//     float m_spacing = 0;
    
//     std::string getText();
//     int getLenght();
//     float getSize();
//     glm::vec4 getColor();

//     void setText(const std::string);
//     void setSize(float size);
//     void setColor(glm::vec4 color);
// };

// } // Namespace OK.