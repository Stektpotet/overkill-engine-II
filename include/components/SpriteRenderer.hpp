#pragma once
#include "components/core/Renderer.hpp"
#include "model/Sprite.hpp"

namespace OK
{
template <typename TextureType>
class SpriteRenderer : public Renderer<Sprite<TextureType>> //TODO: Make InstancedSpriteRenderer
{
    struct defaults
    {
        constexpr static const char * const VERT_SHADER =
            "#version 430\n"
            "layout (location = 0) in vec2 position; layout (location = 1) in vec2 uv;"
            "uniform mat4 m2w; uniform mat4 proj;"
            "out vec2 a;"
            "void main(){a=uv;gl_Position=proj*m2w*vec4(position,0,1);}";

        constexpr static const char * const FRAG_SHADER =
            "#version 430\n"
            "uniform sampler2D image; uniform vec4 color=vec4(1,1,1,1);"
            "in vec2 a;out vec4 b;"
            "void main(){b=color*texture(image,a);}";
    };

protected:
    inline void draw() override
    {
        glm::mat4 m2w = modelToWorldMatrix();
        m2w = glm::translate(m2w, glm::vec3(m_offset.x, m_offset.y, 0.0f));
        //Move origin to rotate around center
        m2w = glm::translate(m2w, glm::vec3(m_pivot.x * m_size.x, m_pivot.y * m_size.y, 0.0f));
        m2w = glm::rotate(m2w, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
        m2w = glm::translate(m2w, glm::vec3(-m_pivot.x * m_size.x, -m_pivot.y * m_size.y, 0.0f));

        m2w = glm::scale(m2w, glm::vec3(m_size, 1.0f));

        m_vertexArray.bind();
        m_material->bind();
        m_material->setProperty({ "model", mvp });
        m_material->setProperty({ "color", m_color});
    }

public:

    //TODO: access constraint, and/or renaming
    float m_rotation = 0;
    glm::vec2 m_offset = glm::vec2(0, 0);          // X-Y offset from transform's position.
    glm::vec2 m_pivot = glm::vec2(0.5f, 0.5f);
    glm::vec2 m_size = glm::vec2(1, 1);

    SpriteRenderer(TextureType texture) : Renderer<Sprite<TextureType>>{ Sprite{ texture } }
    {
        m_material->apply();
    }

    SpriteRenderer(Sprite<TextureType> sprite) : Renderer<Sprite<TextureType>>{ sprite }
    { 
        m_material->apply();
    }

};

} // Namespace OK
