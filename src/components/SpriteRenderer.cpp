#include "components/SpriteRenderer.hpp"

extern glm::vec2 windowSize;

namespace OK
{
    SpriteRenderer::SpriteRenderer( GameObject* gameObject,
                                    Texture2D texture
    ) : Component(gameObject), m_texture{texture}
    {
        prepare();
    }
    
    // https://learnopengl.com/In-Practice/2D-Game/Rendering-Sprites
    void SpriteRenderer::prepare()
    {
        // Configure VAO and VBO
        GLfloat vertices[] = { 
            // Pos      // UV
            0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 1.0f,
            0.0f, 0.0f, 0.0f, 1.0f, 
        
            0.0f, 1.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 1.0f, 0.0f,
            1.0f, 0.0f, 1.0f, 1.0f
        };


        // Setup shader and uniforms:
        m_shader = createProgram("assets/shaders/spriteVertex.vert", "assets/shaders/spriteFragment.frag");

        glm::mat4 projection = glm::ortho(0.0f, static_cast<GLfloat>(windowSize.x), 
        static_cast<GLfloat>(windowSize.y), 0.0f, -1.0f, 1.0f);

	    GFX_GL_CALL(glUniform1i(glGetUniformLocation(m_shader.ID(), "image"), 0));
        GFX_GL_CALL(glUniformMatrix4fv(glGetUniformLocation(m_shader.ID(), "projection"), 1, GL_FALSE, glm::value_ptr(projection)));


        // Setup buffers:
        m_VAO = new VertexArray();
        //VertexBuffer VBO(sizeof(vertices), vertices);
        
        GLuint VBO;
        GFX_GL_CALL(glGenBuffers(1, &VBO));
        GFX_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));
        GFX_GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW));

        GFX_GL_CALL(glEnableVertexAttribArray(0));
        GFX_GL_CALL(glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0));
        
        // Unbind
        GFX_GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0)); 
        GFX_GL_CALL(glBindVertexArray(0));
    }


    void SpriteRenderer::update(float deltaTime)
    {    }

    void SpriteRenderer::draw()
    {
        glm::mat4 mvp = glm::mat4(1);// m_gameObject->m_trasform.modelMatrix();

        mvp = glm::translate(mvp, glm::vec3(m_offset.x, m_offset.y, 0.0f)); 
        
        //Move origin:
        mvp = glm::translate(mvp, glm::vec3(0.5f * m_size.x, 0.5f * m_size.y, 0.0f)); 
        mvp = glm::rotate(mvp, m_rotation, glm::vec3(0.0f, 0.0f, 1.0f)); 
        mvp = glm::translate(mvp, glm::vec3(-0.5f * m_size.x, -0.5f * m_size.y, 0.0f));

        mvp = glm::scale(mvp, glm::vec3(m_size, 1.0f)); 

        m_shader.bind();
        m_texture.bind();

        // Set "update every frame" uniforms:
        GFX_GL_CALL(glUniformMatrix4fv(glGetUniformLocation(m_shader.ID(), "model"), 1, GL_FALSE, glm::value_ptr(mvp)));
        GFX_GL_CALL(glUniform4f(glGetUniformLocation(m_shader.ID(), "spriteColor"), m_color.x, m_color.y, m_color.z, m_color.w));

        m_VAO->bind();
        GFX_GL_CALL(glDrawArrays(GL_TRIANGLES, 0, 6));
        m_VAO->unbind();

        m_texture.unbind();
        m_shader.unbind();
    }

    SpriteRenderer::~SpriteRenderer()
    {
        //delete m_VBO;
    }

}
