#pragma once
#include <vector>
#include <initializer_list>

#include <GL/glew.h>
#include <gfx.h>

class VertexBuffer 
{
private:
    VertexBuffer(GLuint id);
    GLuint id = 0;
    //VertexLayout& layout;

    //TODO: Make restore constructors which build the buffers up from the GPU
public:
	//GLsizeiptr is used because its capacity is larger than that of GLsizei
	VertexBuffer(const GLsizeiptr size, const void * data = nullptr);
	VertexBuffer(const GLsizeiptr size, std::initializer_list<std::pair<const GLsizeiptr, const void*>> data);
	inline ~VertexBuffer() { GFX_DEBUG("VBO (%d) killed in CPU context", id); }

	inline GLuint ID() const { return id; }

	inline bool valid() { return id != 0; }


	inline void bind() const 
    { 
        glBindBuffer(GL_ARRAY_BUFFER, id);
        GFX_DEBUG("VBO (%d) bound", id);
    }
	static inline void unbind() 
    { 
        GFX_DEBUG("VBO unbound");
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
    }
	inline void clear() 
    { 
        GFX_DEBUG("VBO (%d) deleting...", id);
        glDeleteBuffers(1, &id);
    }

	void update(const GLintptr start, const GLsizeiptr size, const void * data);

    static VertexBuffer restore(GLuint id);


};