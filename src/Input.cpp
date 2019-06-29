#include "Input.hpp"

float Input::m_cursorX = 0;
float Input::m_cursorY = 0;
float Input::m_lastCursorX = 0;
float Input::m_lastCursorY = 0;

glm::vec2 Input::CursorDelta()
{
	glm::vec2 delta = glm::vec2(
		(m_cursorX - m_lastCursorX) * 0.01f,
		(m_cursorY - m_lastCursorY) * 0.01f
	);
	m_lastCursorX = m_cursorX;
	m_lastCursorY = m_cursorY;

	return delta;
}

void Input::OnCursorHover(GLFWwindow* window, double x, double y)
{
	m_lastCursorX = m_cursorX;
	m_lastCursorY = m_cursorY;
	m_cursorX = static_cast<float>(x);
	m_cursorY = static_cast<float>(-y);
}
