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

	inline void bind() const { (glBindVertexArray(id)); }
	static inline void unbind() { (glBindVertexArray(0)); }
	inline void clear() {
        glDeleteVertexArrays(1, &id);
    }

private:
	GLuint id = 0;

	//std::unordered_map<GLuint> buffers();
	
	//list layouts, let buffers subscribe to one of them
	//std::vector<VertexLayout> layouts; 
};