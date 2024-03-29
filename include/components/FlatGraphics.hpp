#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "components/GraphicsComponent.hpp"
#include "Structs.hpp"
#include "ResourceLoader.h"

#include "graphics_internal/VertexArray.hpp"
#include "graphics_internal/VertexBuffer.hpp"
#include "graphics_internal/VertexLayout.hpp"
#include "graphics_internal/IndexBuffer.hpp"
#include "graphics_internal/ShaderProgram.hpp"
#include "graphics_internal/Texture.hpp"

namespace OK
{

class FlatGraphics : public GraphicsComponent
{
private:

protected:
    VertexArray m_VAO;     
    glm::mat4 m_projection;
    ShaderProgram m_shader;

    virtual void prepareGraphics();
    void update(float deltaTime) override {}
    virtual void configureShader(ShaderProgram shader){}
    inline void draw() override;

public:

    FlatGraphics();

    float m_rotation = 0;                           // Rotation in radians.
    glm::vec2 m_offset  = glm::vec2(0, 0);          // X-Y offset from transform's position.
    glm::vec2 m_pivot   = glm::vec2(0.5f, 0.5f);
    glm::vec2 m_size    = glm::vec2(1, 1);
    glm::vec4 m_color   = glm::vec4(1, 1, 1, 1);
};

} // Namespace OK