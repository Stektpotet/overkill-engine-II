#include "Transform.hpp"

glm::mat4 Transform::modelMatrix()
{
	return glm::translate(glm::scale(glm::mat4(1.0f), scale) * glm::mat4_cast(rotation), position);
}

void Transform::lookAt(glm::vec3 target, glm::vec3 up)
{
	rotation = glm::lookAt(position, target, up);
}
