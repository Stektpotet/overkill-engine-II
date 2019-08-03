#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <gfx.h>

#include "SpriteRenderer.hpp"

namespace OK
{

class AnimatedSpriteRenderer : public SpriteRenderer<TextureAtlas>
{
private:
    ShaderProgram m_shader;
    VertexArray m_VAO;     // Pointer because it can not be constucted with the object. GL setup must be ran first.

    glm::mat4 m_projection;

protected:
    void awake() override;
    void update(float deltaTime) override;
    void draw() override;
public:
    AnimatedSpriteRenderer(
        GameObject* gameObject,
        int id, 
        TextureAtlas texture
    );
    int m_frame = 0;
    ~AnimatedSpriteRenderer();  // Delete VAO.
};

}
