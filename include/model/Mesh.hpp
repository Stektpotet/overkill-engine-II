#pragma once
#include <vector>
#include <glm.hpp>

#include "../graphics_internal/IndexBuffer.hpp"
#include "../graphics_internal/VertexBuffer.hpp"
#include "../graphics_internal/VertexLayout.hpp"

struct IVertex 
{
    virtual InterleavingVertexLayout  getInterleavingLayout() const = 0;
    virtual ContinuousVertexLayout  getContinuousLayout(int vertices) const = 0;
};

struct Vertex_Full : public IVertex //inspired by unity's appdata_full
{
    glm::vec4 position;    // The vertex position in model space.
    glm::vec3 normal;      // The vertex normal in model space.
    glm::vec4 texcoord;    // The first UV coordinate.
    glm::vec4 texcoord1;   // The second UV coordinate.
    glm::vec4 tangent;     // The tangent vector in Model Space (used for normal mapping).
    glm::vec4 color;       // Per-vertex color

    InterleavingVertexLayout getInterleavingLayout() const override
    {
        return InterleavingVertexLayout{{
                Attribute{ "position", 32, 4, GL_FLOAT },
                Attribute{ "normal", 24, 3, GL_FLOAT },
                Attribute{ "texcoord", 32, 4, GL_FLOAT },
                Attribute{ "texcoord1", 32, 4, GL_FLOAT },
                Attribute{ "tangent", 32, 4, GL_FLOAT },
                Attribute{ "color", 32, 4, GL_FLOAT },
        }};
    }
};

struct Vertex_Base : public IVertex //inspired by unity's appdata_full
{
    glm::vec4 position;    // The vertex position in model space.
    glm::vec3 normal;      // The vertex normal in model space.
    glm::vec4 texcoord;    // The first UV coordinate.
};

struct Vertex_Full_Packed : public IVertex //inspired by unity's appdata_full
{
    glm::vec4 position;    // The vertex position in model space.
    GLint normal;      // The vertex normal in model space.
    GLshort texcoord;    // The first UV coordinate.
    GLshort texcoord1;   // The second UV coordinate.
    GLint tangent;     // The tangent vector in Model Space (used for normal mapping).
    GLint color;       // Per-vertex color

    InterleavingVertexLayout getVertexLayout() const override 
    {

    }
};

template<typename Vertex>
class CPUMesh
{
    VertexLayout layout
public:
    std::vector<Vertex> vertices;
};

class Mesh 
{
protected:
    

};

class BatchedMesh
{
protected:


};