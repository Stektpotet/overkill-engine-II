#pragma once
#include "Camera.hpp"   // Includes Glew, so must be before glfw and /or gfx.
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <gfx.h>
#include "Input.hpp"

namespace OK
{
    

class ControllableCamera : public Camera
{
private:
    float m_moveSpeed;          //units per second
	float m_mouseSensitivity;

public:
    ControllableCamera(
		float fov = 60.0f, 
		float aspectRatio = 4.0f / 3.0f, 
		float near = 0.1f, 
		float far = 200.0f, 
        Transform t = Transform(),
        float moveSpeed = 4,
        float mouseSensitivity = 0.8f        
	);
    
    void update(float deltaTime);

};

}