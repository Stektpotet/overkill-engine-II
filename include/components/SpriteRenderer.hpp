#pragma once
#include "components/core/GraphicsComponent.hpp"

namespace OK
{
template <typename TSprite>
class SpriteRenderer : public GraphicsComponent
{
protected:

    void prepareGraphics() override
    {
        // Setup shader and uniforms:
        //m_sprite.setShaderProgram(createProgram("assets/shaders/spriteVertex.vert", "assets/shaders/spriteFragment.frag"));
        m_sprite.prepare();

        // Configure VAO and VBO
        GLfloat vertices[] = {
            // Pos      // UV
            0.0f, 0.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 0.0f
        };
        GLuint indices[] = {
            0,1,2,
            2,1,3
        };

        // Setup buffers:
        //TODO unify the interface for VBOs and IBOs, the first argument is confusing (count vs size).

        m_vertexArray.bind();
        GFX_ASSERT(m_vertexArray.valid(), "invalid VAO!");
        IndexBuffer<GLuint> ibo(sizeof(indices) / sizeof(indices[0]), indices);
        GFX_ASSERT(ibo.valid(), "invalid IBO!");
        VertexBuffer vbo(sizeof(vertices), vertices);
        GFX_ASSERT(vbo.valid(), "invalid VAO!");

        InterleavingVertexLayout layout;
        layout.pushAttrib<GL_FLOAT, 2, 1, GL_FALSE, false, 8>("position");
        layout.pushAttrib<GL_FLOAT, 2, 1, GL_FALSE, false, 8>("uv");
        layout.applyToBuffer(vbo);
    }

    void draw() override
    {
        m_sprite.spriteToModelSpace() * m_gameObject->m_transform.modelMatrix();
        m_sprite.bind();
        GraphicsComponent::draw();
    }

public:

    SpriteRenderer( TSprite sprite ) : GraphicsComponent(), m_sprite{ sprite }
    { }

    TSprite m_sprite;
};

} // Namespace OK
