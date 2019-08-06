#include "components/TextInstanced.hpp"

extern glm::vec2 windowSize;

namespace OK
{
TextInstanced::TextInstanced(
    GameObject* gameObject, 
    int id, 
    const char* text, 
    const char* fontAtlas
) : FlatGraphics(gameObject, id), 
    m_text{ text },
    c_fontAtlas{ fontAtlas }
{
    if (int err = loadTextureAtlas(c_fontAtlas, 16, &m_asciiMap); err)
    {
        loadTextureAtlas(OK::Fail::error_texture, 2, &m_asciiMap); //recovery
    }
}

void TextInstanced::prepareGraphics()
{
    m_asciiMap.setSamplingOptions(TextureSamplingOptions(GL_LINEAR, GL_CLAMP));
    // Setup shader and uniforms:
    m_shader = createProgram("assets/shaders/text.vert", "assets/shaders/atlasFragment.frag");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowSize.x),
                                      0.0f, static_cast<GLfloat>(windowSize.y), -1.0f, 1.0f);

    GFX_GL_CALL(
        glUniform1iv(m_shader.getUniformLocation("text[0]"), (textLength()+3)/4, (int*)m_text)
    );
    GFX_GL_CALL(glUniform1f(m_shader.getUniformLocation("spacing"), m_spacing));
    GFX_GL_CALL(glUniformMatrix4fv(m_shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection)));
    FlatGraphics::prepareGraphics();
}

void TextInstanced::setText(const char * newText)
{
    m_text = newText;
    //TODO: store currently bound VAO
    //TODO: bind text-VAO
    m_shader.bind();
    GFX_GL_CALL(glUniform1iv(m_shader.getUniformLocation("text[0]"), (textLength() + 3) / 4, (int*)m_text));
    //TODO: rebind previously bound VAO
}
void TextInstanced::draw()
{
    glm::mat4 mvp = m_gameObject->m_transform.modelMatrix();

    mvp = glm::translate(mvp, glm::vec3(m_offset.x, m_offset.y, 0.0f));

    //Move origin to rotate around center
    mvp = glm::translate(mvp, glm::vec3(m_pivot.x * m_size.x, m_pivot.y * m_size.y, 0.0f));
    mvp = glm::rotate(mvp, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    mvp = glm::translate(mvp, glm::vec3(-m_pivot.x * m_size.x, -m_pivot.y * m_size.y, 0.0f));

    mvp = glm::scale(mvp, glm::vec3(m_size, 1.0f));

    m_shader.bind();

    m_asciiMap.bind();
    m_VAO.bind();
    // Set "update every frame" uniforms:
    GFX_GL_CALL(glUniformMatrix4fv(m_shader.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(mvp)));
    GFX_GL_CALL(glUniform4f(m_shader.getUniformLocation("color"), m_color.x, m_color.y, m_color.z, m_color.w));

    configureShader(m_shader);

    GFX_GL_CALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, textLength()));
}

} // Namespace OK.
