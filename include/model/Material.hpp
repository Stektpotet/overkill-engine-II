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
struct Material //TODO: make it a class and restrict access
{
    ShaderProgram m_shader;
    std::vector<Uniform<TextureBase*>> uniformMaps;
    std::vector<Uniform<float>> uniformValues;
    
public:


#pragma region Properties

    template<typename PropertyType>
    void setProperty(Uniform<PropertyType> prop)
    {
        GFX_ERROR(
            "Trying to set property of unsupported type! No known GL-call to apply the uniform \"%s\" {%s}",
            prop.name,
            typeid(prop.value).name()
        );
    }
    template<>
    void setProperty(Uniform<float> prop)
    {
        GFX_GL_CALL(glUniform1f(m_shader.getUniformLocation(prop.name), prop.value));
    }
    template<>
    void setProperty(Uniform<glm::vec4> prop)
    {
        GFX_GL_CALL(
            glUniform4f(
            m_shader.getUniformLocation(prop.name),
            prop.value.x, prop.value.y, prop.value.z, prop.value.w
        )
        );
    }

    template<>
    void setProperty(Uniform<glm::vec4> prop)
    {
        GFX_GL_CALL(
            glUniform4f(
            m_shader.getUniformLocation(prop.name),
            prop.value.x, prop.value.y, prop.value.z, prop.value.w
        )
        );
    }

    template<>
    void setProperty(Uniform<char*> prop)
    {

        GFX_ASSERT(sizeof(prop.name) / sizeof(char) > 128, "Trying to set a uniform with a too long name!");
        char arrayUniformName[128];
        std::strcat(arrayUniformName, prop.name); //TODO: Make more efficient and less prone to error
        std::strcat(arrayUniformName, "[0]");

        GFX_GL_CALL(
            glUniform1iv(
            m_shader.getUniformLocation(arrayUniformName),
            (std::char_traits<char>().length(prop.value) + 3) / 4,
            (int*)(prop.value)
        )
        );
    }
#pragma endregion


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