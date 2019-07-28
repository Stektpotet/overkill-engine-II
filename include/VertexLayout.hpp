//int attribute 0.  -> must match layout in shader
//GLint size
//GLenum type
//GLboolean normalized?
//stride
//array buffer offset
//(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer
#pragma once
#include <GL/glew.h>
#include <vector>
#include <gfx.h>

#include "VertexBuffer.hpp"

struct Attribute 
{
#ifdef DEBUG_GFX
	const char* name;
#endif
	const GLint componentCount;
	const GLint size;
	const GLenum type;
	const GLboolean normalized;

	constexpr Attribute(
		const char* name,
		const GLint size,
		const GLint componentCount,
		const GLenum type,
		const GLboolean normalized)
		:	
#ifdef DEBUG_GFX
			name(name),
#endif
			size(size),
			componentCount(componentCount),
			type(type),
			normalized(normalized)
	{}
};


class VertexLayout 
{	
public:
    using LayoutInitializerList =
        std::initializer_list<std::pair<const char*, std::tuple<GLenum, GLuint, GLint>>>;

private:
	std::vector<Attribute> m_attributes;
	GLuint m_stride = 0;
	inline virtual GLuint addStride(GLint byteSize) const = 0;
public:
    VertexLayout() : m_attributes{}, m_stride{0} {}
    
    VertexLayout(LayoutInitializerList initializer) : m_attributes{}, m_stride{ 0 } {}

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
		m_attributes.emplace_back(name, byteSize, componentCount, type, normalized);
		m_stride += addStride(byteSize);
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
    ContinuousVertexLayout() = default;
    ContinuousVertexLayout(LayoutInitializerList initializer) : VertexLayout(initializer) {}
private:
	inline GLuint addStride(GLint byteSize) const final {return 0;}
};

class InterleavingVertexLayout final : public VertexLayout
{
public:
    InterleavingVertexLayout() = default;
    InterleavingVertexLayout(LayoutInitializerList initializer) : VertexLayout(initializer) {}
private:
	inline GLuint addStride(GLint byteSize) const final { return byteSize; }
};