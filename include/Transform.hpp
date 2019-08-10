#pragma once
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <memory>

namespace OK
{


struct Transform
{
	glm::vec3 position =	{ 0.0f, 0.0f, 0.0f };
	glm::vec3 scale =		{ 1.0f, 1.0f, 1.0f };
	glm::quat rotation = 	{ 1.0f, 0.0f, 0.0f, 0.0f }; //identity
	Transform* m_parent;


	glm::mat4 modelMatrix();
	void lookAt(glm::vec3 axis, glm::vec3 up = { 0.0f, 1.0f, 0.0f });
	void rotateOnAxis(glm::vec3 axis, float radians);

	inline glm::vec3 right()
	{
		return glm::vec3{ 1,0,0 } * rotation;
	}
	inline glm::vec3 up()
	{
		return glm::vec3{ 0,1,0 } * rotation;
	}
	inline glm::vec3 forward()	
	{ 
		return glm::vec3{ 0,0,-1 } * rotation;
	}
};

} // Namespace OK.
