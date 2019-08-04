#include "Transform.hpp"

glm::mat4 Transform::modelMatrix()
{
	glm::mat4 rot = glm::mat4_cast(rotation);
	glm::mat4 scl = glm::scale(glm::mat4(1), scale);
	glm::mat4 trn = glm::translate(glm::mat4(1),  position);
	
	return trn * rot * scl;
}


void Transform::lookAt(glm::vec3 target, glm::vec3 up)
{
	rotation = glm::lookAt(position, target, up);
}

void Transform::rotateOnAxis(glm::vec3 axis, float radians)
{
	rotation = glm::rotate(rotation, radians, axis);
}