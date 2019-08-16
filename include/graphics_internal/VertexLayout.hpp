#pragma once
#include <GL/glew.h>
#include <vector>
#include <gfx.h>

#include "VertexBuffer.hpp"

struct Attribute 
{
	const char* name;
	const GLint componentCount;
	const GLint size;
	const GLenum type;
	const GLboolean normalized = GL_FALSE;

	Attribute(
		const char* name,
		const GLint size,
		const GLint componentCount,
		const GLenum type,
		const GLboolean normalized = GL_FALSE)
		:	
        name{ name },
        size{ size },
        componentCount{ componentCount },
        type{ type },
        normalized{ normalized }
	{}
};


class VertexLayout 
{
private:
	std::vector<Attribute> m_attributes;
protected:
	GLuint m_stride = 0;
	inline virtual void addStride(GLint byteSize) = 0;

    VertexLayout() : m_attributes{}, m_stride{ 0 } {}
    VertexLayout(std::initializer_list<Attribute> attributes) : m_attributes{ attributes }, m_stride{ 0 }
    {
        for (const auto& attr : attributes) 
        {
            addStride(attr.size);
        }
    }

public:

	void applyToBuffer(const VertexBuffer& buffer) 
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
    //NOTE: For some reason, Gfx::GLTypeSize is not reccognized every time, 
    //      making the template very tedious to write out. A new way to write 
    //      layouts is on the way!
    //      (see VertexLayout(LayoutInitializerList initializer))

	template<
		GLenum		 type,
		GLuint		 componentCount,
		GLint		 count = 1,
		GLboolean	 normalized = GL_FALSE,
		bool		 packed = false,
		GLint		 byteSize = (Gfx::GLTypeSize(type) * (packed ? 1 : componentCount) * count)
	>
	void pushAttrib(const char* name)
	{
		GFX_ASSERT((1 <= componentCount && componentCount <= 4) || componentCount == GL_BGRA, "pushing attribute with illegal count: %d (accepted values: 1-4, GL_BGRA)", componentCount);
        m_attributes.push_back(Attribute(name, byteSize, componentCount, type, normalized));
		addStride(byteSize);
	}

	template<
		GLenum		 type,
		GLuint		 componentCount,
		GLint		 count = 1,
		GLboolean	 normalized = GL_TRUE,
		GLint		 byteSize = Gfx::GLTypeSize(type) * count>
	auto pushAttribPacked(const char* name) -> decltype(pushAttrib<type, componentCount, count, normalized, true, byteSize>(name))
	{
		return pushAttrib<type, componentCount, count, normalized, true, byteSize>(name);
	}
};

class ContinuousVertexLayout final : public VertexLayout
{
public: 
    ContinuousVertexLayout() : VertexLayout{} {}
    ContinuousVertexLayout(std::initializer_list<Attribute> initializer) : VertexLayout{ initializer } {}
private:
    inline void addStride(GLint byteSize) final { return; }
};

class InterleavingVertexLayout final : public VertexLayout
{
public:
    InterleavingVertexLayout() : VertexLayout{} {}
    InterleavingVertexLayout(std::initializer_list<Attribute> initializer) : VertexLayout{ initializer } {}
private:
	inline void addStride(GLint byteSize) final {
        m_stride += byteSize; 
    }
};