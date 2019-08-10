#include "components/Sprite.hpp"

extern glm::vec2 windowSize;

namespace OK
{
Sprite::Sprite(
    Texture2D texture
    ) : FlatGraphics(), m_texture{texture}
    {}

void Sprite::prepareGraphics()
{
    // Setup shader and uniforms:
    m_shader = createProgram("assets/shaders/spriteVertex.vert", "assets/shaders/spriteFragment.frag");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowSize.x), 
    0.0f, static_cast<GLfloat>(windowSize.y), -1.0f, 1.0f);
    
    GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation("image"), 0));
    GFX_GL_CALL(glUniformMatrix4fv(m_shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection)));
    FlatGraphics::prepareGraphics();
}

void Sprite::update(float deltaTime)
{
    m_rotation += deltaTime*2;
}

void Sprite::draw()
{        
    m_texture.bind();
    FlatGraphics::draw();
}

} // Namespace OK
