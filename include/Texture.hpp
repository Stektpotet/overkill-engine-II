#pragma once
#include <stdint.h>
#include <vector>
#include <GL/glew.h>
#include <gfx.h>

namespace OK
{
namespace Fail
{
constexpr const char * const error_texture = "assets/texture.png";
}


struct TextureData
{
    uint16_t width = 0u;
    uint16_t height = 0u;
    std::vector<uint8_t> pixels;
};

struct TextureSamplingOptions
{
    GLenum 
        minFilter = GL_NEAREST,
        maxFilter = GL_NEAREST;
    GLenum 
        sWrap = GL_REPEAT,
        tWrap = GL_REPEAT;

    TextureSamplingOptions() = default;
    TextureSamplingOptions(
        GLenum filterMode, GLenum wrapMode
    )   :   minFilter{ filterMode },
            maxFilter{ filterMode },
            sWrap{ wrapMode },
            tWrap{ wrapMode }
    {}

    TextureSamplingOptions(
        GLenum minFilterMode, 
        GLenum maxFilterMode, 
        GLenum sWrapMode, 
        GLenum tWrapMode
    ) : minFilter{ minFilterMode },
        maxFilter{ maxFilterMode },
        sWrap{ sWrapMode },
        tWrap{ tWrapMode }
    {}
};

class TextureBase
{
protected:
    GLuint id;
    uint16_t width, height, channels;
public:
    TextureBase() = default;
    TextureBase(uint16_t width, uint16_t height, uint16_t channels);

    inline void clean() { GFX_GL_CALL(glDeleteTextures(1, &id)); }

    inline bool valid() { return id != 0; }
    inline GLuint getID() { return id; }

    inline uint16_t getWidth() { return width; }
    inline uint16_t getHeight() { return height; }
    inline uint16_t getChannels() { return channels; }
};

template <GLenum TextureType>
class Texture : public TextureBase
{
protected:
public: //TODO: Allow changing of filter and wrapping
    Texture() = default;
    Texture(uint16_t width, uint16_t height, uint16_t channels, TextureSamplingOptions options = TextureSamplingOptions())
        : TextureBase(width, height, channels)
    {
        GFX_GL_CALL(glGenTextures(1, &id));
        GFX_GL_CALL(glBindTexture(TextureType, id));

        GFX_GL_CALL(glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, options.minFilter));
        GFX_GL_CALL(glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, options.maxFilter));

        GFX_GL_CALL(glTexParameteri(TextureType, GL_TEXTURE_WRAP_S, options.sWrap));
        GFX_GL_CALL(glTexParameteri(TextureType, GL_TEXTURE_WRAP_T, options.tWrap));
    }

    inline void bind(GLuint slot = 0) const {
        GFX_GL_CALL(glActiveTexture(GL_TEXTURE0 + slot));
        GFX_GL_CALL(glBindTexture(TextureType, id));
    }
    inline void unbind() const { GFX_GL_CALL(glBindTexture(TextureType, 0)); }

    inline void setSamplingOptions(TextureSamplingOptions options)
    {
        GFX_GL_CALL(glBindTexture(TextureType, id));

        GFX_GL_CALL(glTexParameteri(TextureType, GL_TEXTURE_MIN_FILTER, options.minFilter));
        GFX_GL_CALL(glTexParameteri(TextureType, GL_TEXTURE_MAG_FILTER, options.maxFilter));

        GFX_GL_CALL(glTexParameteri(TextureType, GL_TEXTURE_WRAP_S, options.sWrap));
        GFX_GL_CALL(glTexParameteri(TextureType, GL_TEXTURE_WRAP_T, options.tWrap));

        //NOTE: Might be worth restoring previous bound texture...
    }


    /// <summary>
    /// fetch the uploaded texture from the GPU-memory as raw pixels.
    /// </summary>
    TextureData fetchRaw()
    {
        TextureData data = { width, height, std::vector<uint8_t>(width*height*channels) };
        GFX_GL_CALL(glGetTextureImage(id, 0, GL_RGBA, GL_UNSIGNED_BYTE, width*height, &(data.pixels)[0]));
        return data;
    }
};

using Texture2D = Texture<GL_TEXTURE_2D>; //declare the type as an implementation

class TextureAtlas final : public Texture<GL_TEXTURE_2D_ARRAY>
{
private:
    uint16_t depth/*, sliceDimension*/;
public:
    TextureAtlas() = default;
    TextureAtlas(uint16_t width, uint16_t height, uint16_t depth, uint16_t channels);
    inline uint16_t getDepth() { return depth; }
};

}