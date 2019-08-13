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
    m_shader = createProgram("assets/shaders/particle.vert", "assets/shaders/particle.frag");
    m_shader.bind();

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowSize.x),
                                      0.0f, static_cast<GLfloat>(windowSize.y), -1.0f, 1.0f);

    // Uniform setup:
    GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation("image"), 0));
    GFX_GL_CALL(glUniformMatrix4fv(m_shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection)));

    // Shader storage buffer:
    GFX_GL_CALL(glGenBuffers(1, &m_SSBO));
    GFX_GL_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBO));
    GFX_GL_CALL(glBufferData(GL_SHADER_STORAGE_BUFFER, sizeof(m_data), &m_data, GL_DYNAMIC_COPY));

    FlatGraphics::prepareGraphics();
}

void ParticleSystemSprite::draw()
{

    glm::mat4 mvp = m_gameObject->m_transform.modelMatrix();

    mvp = glm::translate(mvp, glm::vec3(m_offset.x, m_offset.y, 0.0f));

    // Move origin to rotate around center
    mvp = glm::translate(mvp, glm::vec3(m_pivot.x * m_size.x, m_pivot.y * m_size.y, 0.0f));
    mvp = glm::rotate(mvp, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f));
    mvp = glm::translate(mvp, glm::vec3(-m_pivot.x * m_size.x, -m_pivot.y * m_size.y, 0.0f));

    mvp = glm::scale(mvp, glm::vec3(m_size, 1.0f));

    m_shader.bind();
    m_texture.bind();
    m_VAO.bind();
    GFX_GL_CALL(glBindBuffer(GL_SHADER_STORAGE_BUFFER, m_SSBO));

    // Set "update every frame" uniforms:
    GFX_GL_CALL(glUniformMatrix4fv(m_shader.getUniformLocation("model"), 1, GL_FALSE, glm::value_ptr(mvp)));
    GFX_GL_CALL(glUniform4f(m_shader.getUniformLocation("color"), m_color.x, m_color.y, m_color.z,  m_color.w));


    // // Updating of shader storage buffer.
    // TODO: stitch memory together from the different dynamically allocated arrays.
    // This code is using static arrays, which means we always use the most memory possible.
    GLvoid* p = glMapBuffer(GL_SHADER_STORAGE_BUFFER, GL_WRITE_ONLY);
    memcpy(p, &m_shaderData, sizeof(m_shaderData));
    
    GLuint blockIndex = 0;
    blockIndex = glGetProgramResourceIndex(m_shader.ID(), GL_SHADER_STORAGE_BLOCK, "Particles");
    GFX_GL_CALL(glBindBufferBase(GL_SHADER_STORAGE_BUFFER, blockIndex, m_SSBO));

    GLuint ssbo_binding_point_index = 0;
    glShaderStorageBlockBinding(m_shader.ID(), blockIndex, ssbo_binding_point_index);
    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);


    configureShader(m_shader);

    GFX_GL_CALL(glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr, m_highestIndex));
}

} // Namespace OK.