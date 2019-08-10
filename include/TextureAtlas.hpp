#pragma once
#include "graphics_internal/Texture.hpp"

namespace OK
{

class TextureAtlas
{
protected:
    Texture2DArray m_texture;

public:
    TextureAtlas(const char* file, uint16_t width, uint16_t height);
};

}