#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Structs.hpp"
#include "ResourceLoader.h"
#include "components/Component.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ShaderProgram.hpp"
#include "Texture.hpp"

namespace OK
{

class SpriteRenderer : public Component
{
private:
    ShaderProgram m_shader;
    VertexArray* m_VAO;     // Pointer because it can not be constucted with the object. GL setup must be ran first.

    glm::mat4 m_projection;

    void prepare();
    
protected:
    virtual void update(float deltaTime);
    virtual void draw();
public:

    SpriteRenderer(
        GameObject* gameObject,
        int id, 
        Texture2D texture
    );

    float m_rotation = 0;                           // Rotation in degrees.
    glm::vec2 m_offset  = glm::vec2(0, 0);          // X-Y offset from transform's position.
    glm::vec2 m_size    = glm::vec2(1, 1);          
    glm::vec4 m_color   = glm::vec4(1, 1, 1, 1);
    Texture2D m_texture;

    ~SpriteRenderer();  // Delete VAO.
};

}
