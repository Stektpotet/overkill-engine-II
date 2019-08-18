#include "graphics_internal/VertexArray.hpp"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
    GFX_DEBUG("VAO (%d) bound", id);
}
//auto
//VertexArray::sourceAttributes(const int index) -> void
//{
//}
