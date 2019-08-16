#pragma once
#include <glm/glm.hpp>

#include "../graphics_internal/VertexLayout.hpp"

struct Vertex_Full//inspired by unity's appdata_full
{
    glm::vec4 position;    // The vertex position in model space.
    glm::vec3 normal;      // The vertex normal in model space.
    glm::vec2 texcoord;    // The first UV coordinate.
    glm::vec2 texcoord1;   // The second UV coordinate.
    glm::vec4 tangent;     // The tangent vector in Model Space (used for normal mapping).
    glm::vec4 color;       // Per-vertex color

    static InterleavingVertexLayout InterleavingLayout() 
    {
        return InterleavingVertexLayout{ {
                Attribute{ "position", 32, 4, GL_FLOAT },
                Attribute{ "normal", 24, 3, GL_FLOAT },
                Attribute{ "texcoord", 16, 4, GL_FLOAT },
                Attribute{ "texcoord1", 16, 4, GL_FLOAT },
                Attribute{ "tangent", 32, 4, GL_FLOAT },
                Attribute{ "color", 32, 4, GL_FLOAT },
        } };
    }
    static  ContinuousVertexLayout ContinuousLayout(GLuint vertexCount)
    {
        return ContinuousVertexLayout{ {
                Attribute{ "position", 32 * vertexCount, 4, GL_FLOAT },
                Attribute{ "normal", 24 * vertexCount, 3, GL_FLOAT },
                Attribute{ "texcoord", 16 * vertexCount, 4, GL_FLOAT },
                Attribute{ "texcoord1", 16 * vertexCount, 4, GL_FLOAT },
                Attribute{ "tangent", 32 * vertexCount, 4, GL_FLOAT },
                Attribute{ "color", 32 * vertexCount, 4, GL_FLOAT },
        } };
    }
};

struct Vertex_Base //inspired by unity's appdata_full
{
    glm::vec4 position;    // The vertex position in model space.
    glm::vec3 normal;      // The vertex normal in model space.
    glm::vec2 texcoord;    // The first UV coordinate.

    static InterleavingVertexLayout InterleavingLayout()
    {
        return InterleavingVertexLayout{ {
                Attribute{ "position", 32, 4, GL_FLOAT },
                Attribute{ "normal", 24, 3, GL_FLOAT },
                Attribute{ "texcoord", 16, 4, GL_FLOAT }
        } };
    }
    static ContinuousVertexLayout ContinuousLayout(GLuint vertexCount)
    {
        return ContinuousVertexLayout{ {
                Attribute{ "position", 32 * vertexCount, 4, GL_FLOAT },
                Attribute{ "normal", 24 * vertexCount, 3, GL_FLOAT },
                Attribute{ "texcoord", 16 * vertexCount, 4, GL_FLOAT }
        } };
    }
};

struct Vertex_Full_Packed//inspired by unity's appdata_full
{
    glm::vec4 position;    // The vertex position in model space.
    GLint normal;      // The vertex normal in model space.
    GLushort texcoord;    // The first UV coordinate.
    GLushort texcoord1;   // The second UV coordinate.
    GLint tangent;     // The tangent vector in Model Space (used for normal mapping).
    GLint color;       // Per-vertex color

    static InterleavingVertexLayout InterleavingLayout()
    {
        return InterleavingVertexLayout{ {
                Attribute{ "position", 32, 4, GL_FLOAT },
                Attribute{ "normal", 4, 3, GL_INT_2_10_10_10_REV, GL_TRUE },
                Attribute{ "texcoord", 2, 4, GL_UNSIGNED_SHORT, GL_TRUE },
                Attribute{ "texcoord1", 2, 4, GL_UNSIGNED_SHORT, GL_TRUE },
                Attribute{ "tangent", 4, 4, GL_INT_2_10_10_10_REV, GL_TRUE },
                Attribute{ "color", 4, 4, GL_UNSIGNED_INT_8_8_8_8 },
        } };
    }
    static ContinuousVertexLayout ContinuousLayout(GLuint vertexCount)
    {
        return ContinuousVertexLayout{ {
                Attribute{ "position", 32 * vertexCount, 4, GL_FLOAT },
                Attribute{ "normal", 4 * vertexCount, 3, GL_INT_2_10_10_10_REV, GL_TRUE },
                Attribute{ "texcoord", 2 * vertexCount, 4, GL_UNSIGNED_SHORT, GL_TRUE },
                Attribute{ "texcoord1", 2 * vertexCount, 4, GL_UNSIGNED_SHORT, GL_TRUE },
                Attribute{ "tangent", 4 * vertexCount, 4, GL_INT_2_10_10_10_REV, GL_TRUE },
                Attribute{ "color", 4 * vertexCount, 4, GL_UNSIGNED_INT_8_8_8_8 },
        } };
    }
};

