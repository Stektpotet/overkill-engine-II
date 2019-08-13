#pragma once
#include <vector>
#include <initializer_list>

#include "Vertex.hpp"
#include "Material.hpp"
#include "../graphics_internal/IndexBuffer.hpp"
#include "../graphics_internal/VertexBuffer.hpp"
#include "../graphics_internal/VertexLayout.hpp"

//TODO: Create a MakeMesh()-call to simply upload mesh to graphics card, and counterpart FetchMesh
namespace OK
{
class Drawable
{
protected:
    VertexBuffer m_vertexBuffer;
    IndexBuffer<GLuint> m_indexBuffer;
    
    std::shared_ptr<Material> m_material;
    
    Drawable() = default;
    template<typename VertexType>
    Drawable(CPUMesh<VertexType> data) :
        m_vertexBuffer{ data.verticesByteSize(), data.vertices.data() },
        m_indexBuffer{ data.indexCount(), data.indices.data() }
    {}

public:
    void bind()
    {
        m_indexBuffer.bind();
        m_vertexBuffer.bind();
    }
};

template<typename TVertex>
class CPUMesh
{
public:
    std::vector<TVertex> vertices;
    std::vector<GLuint> indices;

    CPUMesh(std::initializer_list<TVertex> vertices, std::initializer_list<GLuint> indices) : vertices{ vertices }, indices{ indices } {}
    CPUMesh(std::vector<TVertex> vertices, std::vector<GLuint> indices) : vertices{ vertices }, indices{ indices } {}

    inline GLsizeiptr verticesByteSize() const { return vertices.size() * sizeof(TVertex); }
    inline GLsizeiptr indexCount() const { return indices.size(); }
};

template<typename TVertex>
class Mesh : public Drawable
{
    CPUMesh<TVertex> m_mesh;
protected:
    Mesh(CPUMesh<TVertex> data) : Drawable(data), m_mesh{ data }
    {
        TVertex::InterleavingLayout().applyToBuffer(m_vertexBuffer);
    }
};

template<typename TVertex>
class BatchedMesh : public Drawable
{
    std::vector<CPUMesh<TVertex>> m_submeshes;
protected:
    BatchedMesh(std::vector<CPUMesh<TVertex>> submeshes) :
        m_submeshes{ submeshes }
    {
        GLsizeiptr totalVertexSize = 0;
        GLsizeiptr totalIndexCount = 0;
        for (const auto& submesh : m_submeshes)
        {
            totalVertexSize += submesh.verticesByteSize();
            totalIndexCount += submesh.indexCount();
        }

        m_vertexBuffer = VertexBuffer{ totalVertexSize };
        m_indexBuffer = IndexBuffer<GLuint>{ totalIndexCount };
        GLsizeiptr vertexBufferIndex = 0;
        GLsizeiptr IndexBufferIndex = 0;
        for (const auto& submesh : m_submeshes)
        {
            m_vertexBuffer.update(vertexBufferIndex, submesh.verticesByteSize(), submesh.vertices.data() + vertexBufferIndex);
            vertexBufferIndex += submesh.verticesByteSize();

            m_indexBuffer.update(IndexBufferIndex, submesh.indexCount() * sizeof(GLuint), submesh.indices.data() + indexBufferIndex);
            IndexBufferIndex += submesh.indexCount() * sizeof(GLuint);
        }

        TVertex::InterleavingLayout().applyToBuffer(m_vertexBuffer);
    }
};
}