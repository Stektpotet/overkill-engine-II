#pragma once
#include <vector>
#include <unordered_map>
#include <gfx.h>

#include "VertexLayout.hpp"

class VertexArray
{
public:
	VertexArray();
	inline ~VertexArray() { glDeleteVertexArrays(1, &id); }

	inline bool valid() { return id != 0; }

	inline void bind() const { (glBindVertexArray(id)); }
	static inline void unbind() { (glBindVertexArray(0)); }
	inline void clear() { (glDeleteBuffers(1, &id)); }

private:
	GLuint id = 0;

	//std::unordered_map<GLuint> buffers();
	
	//list layouts, let buffers subscribe to one of them
	std::vector<VertexLayout> layouts; 
};