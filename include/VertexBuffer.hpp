#pragma once
#include <vector>
#include <initializer_list>

#include <GL/glew.h>
#include <gfx.h>

class VertexBuffer 
{
public:
	//GLsizeiptr is used because its capacity is larger than that of GLsizei
	VertexBuffer(const GLsizeiptr size, const void * data = nullptr);
	VertexBuffer(const GLsizeiptr size, std::initializer_list<std::pair<const GLsizeiptr, const void*>> data);
	inline ~VertexBuffer() { glDeleteBuffers(1, &id); }

	inline GLuint ID() const { return id; }

	inline bool valid() { return id != 0; }


	inline void bind() const { glBindBuffer(GL_ARRAY_BUFFER, id); }
	static inline void unbind() { glBindBuffer(GL_ARRAY_BUFFER, 0); }
	inline void clear() { glDeleteBuffers(1, &id); }

	//void resize(const GLsizeiptr size);
	void update(const GLintptr start, const GLsizeiptr size, const void * data);
	//void setLayout(const VertexLayout& newLayout) { layout = newLayout; }

private:
	GLuint id=0;
	//VertexLayout& layout;
};