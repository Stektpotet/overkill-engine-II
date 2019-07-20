#include "components/SpriteRenderer.hpp"

namespace OK
{
    SpriteRenderer::SpriteRenderer( GameObject* gameObject,
                                    Texture2D texture,
                                    glm::vec2 offset,
                                    glm::vec2 size,
                                    glm::vec4 color,
                                    float rotation
                                ) : Component(gameObject)
    {
        m_texture = texture;
        m_offset = offset;
        m_size = size;
        m_color = color;
        m_rotation = rotation;
        
        prepare();
    }
    
    // https://learnopengl.com/In-Practice/2D-Game/Rendering-Sprites
    void SpriteRenderer::prepare()
    {
        // Configure VAO and VBO
        GLfloat vertices[] = { 
            // Pos      // UV
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f, 0.0f, 
        
            0.0f, 1.0f, 0.0f, 1.0f,
            1.0f, 1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f, 0.0f
        };
        
        m_VBO = new VertexBuffer(sizeof(vertices), vertices);
        m_shader = createProgram("assets/shaders/spriteVertex.vert", "assets/shaders/spriteFragment.frag");

        GFX_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, m_VBO->ID()));
        GFX_GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        GFX_GL_CALL(glBindVertexArray(m_VAO.ID()));
        GFX_GL_CALL(glEnableVertexAttribArray(0));
        GFX_GL_CALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0));
        GFX_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); 
        GFX_GL_CALL(glBindVertexArray(0));
        
    }


    void SpriteRenderer::update(float deltaTime)
    {    }

    void SpriteRenderer::draw()
    {
        glm::mat4 mvp = m_gameObject->m_trasform.modelMatrix();

        mvp = glm::translate(mvp, glm::vec3(m_offset.x, m_offset.y, 0.0f)); 
        
        //Move origin:
        mvp = glm::translate(mvp, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.0f)); 
        mvp = glm::rotate(mvp, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
        mvp = glm::translate(mvp, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.0f));

        mvp = glm::scale(mvp, glm::vec3(m_size, 1.0f)); 


        m_shader.bind();
        m_VAO.bind();
        m_texture.bind();

	    GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation("image"), 0));
        // set texture uniform
	    GLuint mvpLocation = glGetUniformLocation(m_shader.ID(), "MVP");
	    glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, glm::value_ptr(mvp));
        
        GFX_GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));

        m_VAO.unbind();
        m_texture.unbind();
        m_shader.unbind();
    }

    SpriteRenderer::~SpriteRenderer()
    {
        delete m_VBO;
    }

}
