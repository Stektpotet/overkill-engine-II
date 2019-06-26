#include "Input.hpp"

float Input::m_cursorX = 0;
float Input::m_cursorY = 0;
float Input::m_cursorDeltaX = 0;
float Input::m_cursorDeltaY = 0;

glm::vec2 Input::CursorDelta()
{
	return glm::vec2(m_cursorDeltaX, m_cursorDeltaY);
}

void Input::OnCursorHover(GLFWwindow* window, double x, double y)
{
	m_cursorDeltaX = float(x) - m_cursorX;
	m_cursorDeltaY = float(y) - m_cursorY;
	m_cursorX = float(x);
	m_cursorY = float(y);
}
