#pragma once

#include <glm/glm.hpp>
#include "graphics_internal/Texture.hpp"
#include "graphics_internal/ShaderProgram.hpp"
#include "ResourceLoader.h"

namespace OK
{

template<typename TTexture>
class BaseSprite
{
public:

protected:
    TTexture m_texture;
    ShaderProgram m_shader;
    BaseSprite(TTexture texture) : m_texture{ texture }
    {}

public:
    float m_rotation = 0;
    glm::vec2 m_offset = glm::vec2(0, 0);          // X-Y offset from transform's position.
    glm::vec2 m_pivot = glm::vec2(0.5f, 0.5f);
    glm::vec2 m_size = glm::vec2(1, 1);
    
    inline void bind() { m_texture.bind(); }
    
    inline void setShaderProgram(ShaderProgram& shader)
    { 
        m_shader = shader; 
        prepare(); //update uniforms of newly changed to shader program
    }

    virtual void prepare()
    {
        glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowSize.x),
                                          0.0f, static_cast<GLfloat>(windowSize.y), -1.0f, 1.0f);

        GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation("image"), 0));
        GFX_GL_CALL(glUniformMatrix4fv(m_shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection)));
    }

    glm::mat4 spriteToModelSpace()
    {
        glm::mat4 m = glm::translate(glm::mat4(1), glm::vec3(m_offset.x, m_offset.y, 0.0f));

        //Move origin to rotate around pivot
        m = glm::translate(m, glm::vec3(m_pivot.x * m_size.x, m_pivot.y * m_size.y, 0.0f));
        m = glm::rotate(m, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        m = glm::translate(m, glm::vec3(-m_pivot.x * m_size.x, -m_pivot.y * m_size.y, 0.0f));

        return glm::scale(m, glm::vec3(m_size, 1.0f));
    }
};

//TODO: Move these subclasses' defs into cpp-files

class Sprite : public BaseSprite<Texture2D>
{
public:
    struct defaults
    {
        constexpr static const char * const VERT_SHADER =
            "#version 430\n"
            "layout (location = 0) in vec2 position; layout (location = 1) in vec2 uv;"
            "uniform mat4 model; uniform mat4 projection;"
            "out vec2 a;"
            "void main(){a=uv;gl_Position=projection*model*vec4(position,0,1);}";

        constexpr static const char * const FRAG_SHADER =
            "#version 430\n"
            "uniform sampler2D image; uniform vec4 color=vec4(1,1,1,1);"
            "in vec2 a;out vec4 b;"
            "void main(){b=color*texture(image,a);}";
    };

public:
    Sprite( Texture2D texture ) : BaseSprite(texture)  
    {
        m_shader = createProgramRaw(defaults::VERT_SHADER, defaults::FRAG_SHADER);
    }

}; 

class AtlasSprite : public BaseSprite<Texture2DArray>
{
public:

    struct defaults
    {
        constexpr static const char * const VERT_SHADER =
            "#version 430\n"
            "layout (location = 0) in vec2 position; layout (location = 1) in vec2 uv;"
            "uniform mat4 model;uniform mat4 projection;uniform int a;"
            "out vec3 b;"
            "void main(){b=vec3(uv,a);gl_Position=projection*model*vec4(position,0,1);}";

        constexpr static const char * const FRAG_SHADER =
            "#version 430\n"
            "uniform sampler2DArray image;uniform vec4 color=vec4(1,1,1,1);"
            "in vec3 b;out vec4 c;"
            "void main() {c=color*texture(image,b);}";
    };

private:
    int m_atlasIndex;
public:

    AtlasSprite( Texture2DArray texture ) : BaseSprite(texture), m_atlasIndex{0}
    {
        m_shader = createProgramRaw(defaults::VERT_SHADER, defaults::FRAG_SHADER);
    }
    void prepare() override {
        BaseSprite::prepare();
        GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation("a"), m_atlasIndex));
    }
    void setAtlasIndex(int i)
    {
        m_atlasIndex = i;
        GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation("a"), m_atlasIndex));
    }
};

}