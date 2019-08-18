#pragma once
#include <vector>
#include <unordered_map>
#include <gfx.h>

#include "VertexLayout.hpp"

class VertexArray
{
public:
	VertexArray();
    inline ~VertexArray() { GFX_DEBUG("VAO (%d) killed in CPU context", id); }

	inline bool valid() { return id != 0; }
	inline GLuint ID() const { return id; }

	inline void bind() const 
    { 
        GFX_DEBUG("VAO (%d) bound", id);
        GFX_GL_CALL(glBindVertexArray(id)); 
    }
	static inline void unbind() 
    { 
        GFX_DEBUG("VAO unbound");
        GFX_GL_CALL(glBindVertexArray(0)); 
    }
	inline void clear() {
        GFX_DEBUG("VAO (%d) deleting...", id);
        glDeleteVertexArrays(1, &id);
    }

private:
	GLuint id = 0;

	//std::unordered_map<GLuint> buffers();
	
	//list layouts, let buffers subscribe to one of them
	//std::vector<VertexLayout> layouts; 
};