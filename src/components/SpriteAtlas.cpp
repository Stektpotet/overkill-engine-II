#include "components/SpriteAtlas.hpp"

extern glm::vec2 windowSize;

namespace OK
{

SpriteAtlas::SpriteAtlas(
    TextureAtlas atlas,
    int atlasIndex
    ) : FlatGraphics(), 
    m_atlas{atlas}, 
    m_atlasIndex{atlasIndex}
    {}

void SpriteAtlas::prepareGraphics()
{
    // Setup shader and uniforms:
    m_shader = createProgram("assets/shaders/atlas.vert", "assets/shaders/atlasFragment.frag");

    glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowSize.x), 
    0.0f, static_cast<GLfloat>(windowSize.y), -1.0f, 1.0f);
    
    GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation("image"), 0));
    GFX_GL_CALL(glUniformMatrix4fv(m_shader.getUniformLocation("projection"), 1, GL_FALSE, glm::value_ptr(projection)));
    FlatGraphics::prepareGraphics();
}

void SpriteAtlas::update(float deltaTime)
{
    m_rotation += deltaTime*2;
}

void SpriteAtlas::configureShader(ShaderProgram shader)
{
    if (m_atlasIndex >= 0)
    {
        GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation("atlasIndex"), m_atlasIndex));
    }
    else
    {
        GFX_ERROR("SpriteAtlas does not have an index in the TextureAtlas to render. Missing atlasIndex.");
    }
}

void SpriteAtlas::draw()
{        
    if (m_atlasIndex >= 0)
        m_atlas.bind();
    else
        GFX_ERROR("SpriteAtlas does not have an index in the TextureAtlas to render. Missing atlasIndex.");
    
    FlatGraphics::draw();
}

} // Namespace OK
