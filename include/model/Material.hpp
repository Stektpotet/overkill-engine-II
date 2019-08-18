#pragma once
#include <vector>

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
    Material(ShaderProgram program);

    ShaderProgram m_shader;
    std::vector<Uniform<TextureBase*>> uniformMaps;
    std::vector<Uniform<float>> uniformValues;
    
public:
    template<typename PropertyType>
    void setProperty(Uniform<PropertyType> prop);

    //bind the shader, the material stays as last bound
    void bind();

    //apply the material to the shader
    void apply();
};

}