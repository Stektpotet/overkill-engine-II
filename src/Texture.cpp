#include "Texture.hpp"

TextureAtlas::TextureAtlas(uint16_t width, uint16_t height, uint16_t depth, uint16_t channels) 
	:	Texture(width, height, channels), 
		depth(depth)
{}
