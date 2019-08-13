#pragma once
#include <vector>
#include <glm/glm.hpp>

#include "../graphics_internal/ShaderProgram.hpp"
#include "../graphics_internal/Texture.hpp"

namespace OK
{

template<typename T>
struct Uniform
{
    const char* name;
    T value;
};

//CPU-bound configuration of shader's uniforms
class Material
{
    ShaderProgram m_shader;
    std::vector<Uniform<TextureBase*>> uniformMaps;
    std::vector<Uniform<float>> uniformValues;

public:
    //bind the shader, the material stays as last bound
    void bind()
    {   
        //TODO: verify statefulness of shaders, my suspicion is that their state
        //      is not kept, meaning we will need to reapply every time.
        m_shader.bind();
    }

    //apply the material to the shader
    void apply() 
    {
        m_shader.bind();
        for (const auto& uniform : uniformValues)
        {
            GFX_GL_CALL(glUniform1f(m_shader.getUniformLocation(uniform.name), uniform.value));
        }
        int mapsBound = 0;
        for (const auto& uniform : uniformMaps)
        {
            uniform.value->bind(mapsBound);
            GFX_GL_CALL(glUniform1i(m_shader.getUniformLocation(uniform.name), mapsBound));
            mapsBound++;
        }
    }
};

}