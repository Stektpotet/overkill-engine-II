#pragma once
#include <GL/glew.h>

#include "Transform.hpp"

namespace OK
{

enum class CameraMode
{
	Free,
	Orbital,
	Locked
};

class Camera 
{
private: 
	float fieldOfViewVertical = glm::radians(45.0f);
	float aspectRatio=4.0f/3.0f;
	float nearClip=0.1f, farClip=200;
public:
	Transform transform;


public:
	Camera(
		float fov = 60.0f, 
		float aspectRatio = 4.0f / 3.0f, 
		float near=0.1f, 
		float far=200.0f, 
		Transform t = Transform()
	);

	inline void setFoV(float fovHorizontal) 
	{ fieldOfViewVertical = glm::radians(fovHorizontal * (1.0f / aspectRatio)); }
	
	glm::mat4 viewMatrix();
	glm::mat4 viewProjectionMatrix();

};

}