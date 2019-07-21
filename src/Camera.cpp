#include "Camera.hpp"

namespace OK
{

Camera::Camera(
	float fov,			// = 60.0f
	float aspectRatio,  // = 4.0f/3.0f
	float near,			// = 0.1f
	float far,			// = 200.0f
	Transform t			// = Transform()
)	:	
	fieldOfViewVertical(glm::radians(fov * (1.0f / aspectRatio))),
	aspectRatio(aspectRatio),
	nearClip(near),
	farClip(far),
	transform(t)
{}

glm::mat4 Camera::viewMatrix()
{
	return glm::translate(glm::mat4_cast(transform.rotation), -transform.position); //scale not needed, cameras can't scale..
}

glm::mat4 Camera::viewProjectionMatrix()
{
	return 
		glm::perspective(fieldOfViewVertical, aspectRatio, nearClip, farClip) * 
		glm::translate(glm::mat4_cast(transform.rotation), -transform.position);
}

}