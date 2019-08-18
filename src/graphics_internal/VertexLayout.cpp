#include "graphics_internal/VertexLayout.hpp"

//TODO: put all the things in here

VertexLayout::VertexLayout() : m_attributes{}, m_stride{ 0 } {}
VertexLayout::VertexLayout(std::initializer_list<Attribute> attributes) : m_attributes{ attributes }, m_stride{ 0 }
{
    for (const auto& attr : attributes)
    {
        addStride(attr.size);
    }
}
void VertexLayout::applyToBuffer(const VertexBuffer& buffer)
{
    //NOTE: assumes bound VertexArray
    buffer.bind();
    GLuint i = 0;
    GLuint offset = 0;
    for (const auto& attrib : m_attributes)
    {
        GFX_GL_CALL(glEnableVertexAttribArray(i)); //TODO: NOTE - assuming correct layout
        GFX_GL_CALL(glVertexAttribPointer(			//TODO: Look into managing bindings self
                    i,							// location
                    attrib.componentCount,		// size
                    attrib.type,				// type
                    attrib.normalized,			// normalized
                    m_stride,					// stride - byte offset till next of same attribute
                    (const void*)offset			// array buffer offset
        ));
        offset += attrib.size;
        i++;
    }
}


ContinuousVertexLayout::ContinuousVertexLayout(
    std::initializer_list<Attribute> initializer
) : VertexLayout{ initializer }
{
}
inline void ContinuousVertexLayout::addStride(GLuint byteSize){/*Do nothing*/}


InterleavingVertexLayout::InterleavingVertexLayout(
    std::initializer_list<Attribute> initializer
) : VertexLayout{ initializer } 
{
}

inline void InterleavingVertexLayout::addStride(GLuint byteSize)
{
    m_stride += byteSize;
}