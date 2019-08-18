#include "model/Material.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OK
{

void Material::bind()
{
    //TODO: verify statefulness of shaders, my suspicion is that their state
    //      is not kept, meaning we will need to reapply every time.
    m_shader.bind();
}

void Material::apply()
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

#pragma region Properties

template<typename PropertyType>
void Material::setProperty(Uniform<PropertyType> prop)
{
    GFX_ERROR(
        "Trying to set property of unsupported type! No known GL-call to apply the uniform \"%s\" {%s}",
        prop.name,
        typeid(prop.value).name()
    );
}
template<>
void Material::setProperty(Uniform<float> prop)
{
    GFX_GL_CALL(glUniform1f(m_shader.getUniformLocation(prop.name), prop.value));
}
template<>
void Material::setProperty(Uniform<glm::vec4> prop)
{
    GFX_GL_CALL(
        glUniform4f(
        m_shader.getUniformLocation(prop.name),
        prop.value.x, prop.value.y, prop.value.z, prop.value.w
    )
    );
}

template<>
void Material::setProperty(Uniform<glm::mat4> prop)
{
    GFX_GL_CALL(
        glUniformMatrix4fv(
        m_shader.getUniformLocation(prop.name), 
        1, 
        GL_FALSE, 
        glm::value_ptr(prop.value)
    )
    );
}

template<>
void Material::setProperty(Uniform<char*> prop)
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

} //namespace OK