#pragma once
#include "components/TextInstanced.hpp"
#include "ResourceLoader.h"
extern glm::vec2 windowSize;

namespace OK
{
TextInstanced::TextInstanced(
    const char* text, 
    const uint16_t dimensionWidth,
    const uint16_t dimensionHeight,
    const char* fontAtlas
) : SpriteRenderer{ loadTextureAtlas(fontAtlas, dimensionWidth, dimensionHeight) },
    m_text{ text }
{
}

void TextInstanced::prepareGraphics()
{
    m_drawable->m_texture.setSamplingOptions(TextureSamplingOptions(GL_LINEAR, GL_CLAMP));
    // Setup shader and uniforms:
    m_material->m_shader = createProgram("assets/shaders/text.vert", "assets/shaders/atlasFragment.frag");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowSize.x),
                                      0.0f, static_cast<GLfloat>(windowSize.y), -1.0f, 1.0f);

    GFX_GL_CALL(
        glUniform1iv(m_material->m_shader.getUniformLocation("text[0]"), (textLength()+3)/4, (int*)m_text)
    );
    m_material->setProperty(Uniform<float>{ "spacing", m_spacing });
    m_material->setProperty(Uniform<glm::mat4>{ "projection", projection});
    Renderer::prepareGraphics();
}

void TextInstanced::setText(const char * newText)
{
    m_text = newText;
    //TODO: store currently bound VAO
    //TODO: bind text-VAO
    m_material->apply(); //TOOD: check if bind is sufficient
    GFX_GL_CALL(glUniform1iv(m_material->m_shader.getUniformLocation("text[0]"), (textLength() + 3) / 4, (int*)m_text));
    //TODO: rebind previously bound VAO
}
void TextInstanced::draw()
{
    SpriteRenderer::draw();

    GFX_GL_CALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, textLength()));
}

} // Namespace OK.
