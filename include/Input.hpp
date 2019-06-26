#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <gfx.h>
class Input 
{
private:
	static float m_cursorX, m_cursorY;
	static float m_cursorDeltaX, m_cursorDeltaY;

public:
	static glm::vec2 CursorDelta();

	static void OnCursorHover(GLFWwindow* window, double x, double y);
};