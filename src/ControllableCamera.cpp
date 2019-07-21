#include "ControllableCamera.hpp"

extern  GLFWwindow* window;

namespace OK
{
    

ControllableCamera::ControllableCamera( float fov,
                                        float aspectRatio,
                                        float near,
                                        float far,
                                        Transform t,
                                        float moveSpeed,
                                        float mouseSensitivity
                                    ) : Camera(fov, aspectRatio, near, far, t)
    {
        m_moveSpeed = moveSpeed;
        m_mouseSensitivity = mouseSensitivity;
    }


void ControllableCamera::update(float deltaTime)
{
    // Transation:
    if (glfwGetKey(window, GLFW_KEY_A)) 
    {
        transform.position -= transform.right() * m_moveSpeed * deltaTime;
    } 
    else if (glfwGetKey(window, GLFW_KEY_D)) 
    {
        transform.position += transform.right() * m_moveSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_W))
    {
        transform.position += transform.forward() * m_moveSpeed * deltaTime;
    }
    else if (glfwGetKey(window, GLFW_KEY_S))
    {
        transform.position -= transform.forward() * m_moveSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_Q))
    {
        transform.position -= transform.up() * m_moveSpeed * deltaTime;
    }
    else if (glfwGetKey(window, GLFW_KEY_E))
    {
        transform.position += transform.up() * m_moveSpeed * deltaTime;
    }

    // Rotation:
	auto delta = Input::CursorDelta();

	//GFX_DEBUG("delta(%f,%f)", delta.x, delta.y);
	transform.rotation = glm::rotate(transform.rotation, delta.x * m_mouseSensitivity, transform.up());
	transform.rotation = glm::rotate(transform.rotation, delta.y * m_mouseSensitivity, -transform.right());

	/*glm::quat deltaRotation = glm::normalize(
		glm::vec3(delta.x * mouseSensitivity, delta.y * mouseSensitivity, 1.0f)
	) * glm::quat {1,0,0,0};

	cam.transform.rotation = cam.transform.rotation * deltaRotation;*/

	
}

}