#include "TextureAtlas.hpp"
#include "ResourceLoader.h"
namespace OK
{

TextureAtlas::TextureAtlas( const char* file, uint16_t width, uint16_t height)
{
    if (auto err = loadTextureAtlas(file, dimension, &m_texture); err) 
    {
        loadTextureAtlas(OK::Fail::error_texture, 1, &m_texture);
    }
}

}