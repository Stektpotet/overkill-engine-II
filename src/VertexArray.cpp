#include <VertexArray.hpp>

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &id);
	glBindVertexArray(id);
}
//auto
//VertexArray::sourceAttributes(const int index) -> void
//{
//}
