#include "components/ParticleSystemSprite.hpp"

extern glm::vec2 windowSize;

namespace OK
{

ParticleSystemSprite::ParticleSystemSprite( Texture2D texture,
                                            int maxParticles,
                                            ParticleSystemConfiguration config) 
                                            : ParticleSystem(maxParticles, config),
                                            m_texture{texture}
{
}


void ParticleSystemSprite::prepareGraphics()
{
    m_texture.setSamplingOptions(TextureSamplingOptions(GL_LINEAR, GL_CLAMP));

    // Setup shader and uniforms:
    m_shader = createProgram("assets/shaders/particle.vert", "assets/shaders/sprite.frag");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowSize.x),
                                      0.0f, static_cast<GLfloat>(windowSize.y), -1.0f, 1.0f);

    m_shader.bind();
     GFX_GL_CALL(
            glUniform3fv(m_shader.getUniformLocation("pos[0]"), m_maxParticles,  glm::value_ptr(pos[0]))
        );

    GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation("image"), 0));
    GFX_GL_CALL(glUniformMatrix4fv(m_shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection)));
    FlatGraphics::prepareGraphics();
}

void ParticleSystemSprite::draw()
{
    m_shader.bind();
    for (int i = 0; i < m_count; i++)
    {
        //char s[10];
        //sprintf(s, "pos[%d]", i);
        GFX_GL_CALL(
            glUniform3fv(m_shader.getUniformLocation("pos[0]"), m_maxParticles,  glm::value_ptr(pos[0]))
        );
    }


    glm::mat4 mvp = m_gameObject->m_transform.modelMatrix();

    mvp = glm::translate(mvp, glm::vec3(m_offset.x, m_offset.y, 0.0f));

    //Move origin to rotate around center
    mvp = glm::translate(mvp, glm::vec3(m_pivot.x * m_size.x, m_pivot.y * m_size.y, 0.0f));
    mvp = glm::rotate(mvp, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    mvp = glm::translate(mvp, glm::vec3(-m_pivot.x * m_size.x, -m_pivot.y * m_size.y, 0.0f));

    mvp = glm::scale(mvp, glm::vec3(m_size, 1.0f));

    // m_shader.bind();

    m_texture.bind();
    m_VAO.bind();
    // Set "update every frame" uniforms:
    GFX_GL_CALL(glUniformMatrix4fv(m_shader.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(mvp)));
    GFX_GL_CALL(glUniform4f(m_shader.getUniformLocation("color"), color[0].x, color[0].y, color[0].z, color[0].z));

    configureShader(m_shader);

    GFX_GL_CALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_count));
}

} // Namespace OK.