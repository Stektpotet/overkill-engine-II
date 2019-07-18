#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include "components/Component.hpp"
#include "Texture.hpp"

namespace OK
{

class SpriteRenderer : Component
{
private:
    Texture2D m_texture;
    glm::vec2 m_size;
    glm::vec4 m_color;
public:
    SpriteRenderer(Texture2D texture, glm::vec2 size, glm::vec4 color);
};

}
