#include "FengShuiEngine_PCH.h"
#include "InputManager.h"
#include <GLFW\glfw3.h>
#include <algorithm>
#include <iostream>
#include "Window\Window.h"
#include "Window\GLWindow.h"

DEFINE_SINGLETON(InputManager)

InputManager::InputManager()
: m_mousePosition(0.0f, 0.0f), m_lastFrameMousePosition(0.0f, 0.0f), m_mousePositionDelta(0.0f, 0.0f)
{
}

InputManager::~InputManager()
{
}

void InputManager::Init(Window* window)
{
	GLFWwindow* glWindowObject = (dynamic_cast<GLWindow*>(window))->m_window;
	if (glWindowObject != nullptr)
	{
		glfwSetKeyCallback(glWindowObject, &InputManager::StaticKeyboardKeyCallback);
		glfwSetCursorPosCallback(glWindowObject, &InputManager::StaticCursorPositionCallback);
		glfwSetMouseButtonCallback(glWindowObject, &InputManager::StaticMouseButtonCallback);

		//glfwSetInputMode(glWindowObject, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}	
}

void InputManager::Update()
{	
	//DebugKeyboardInput();
	//DebugMouseInput();

	m_mousePositionDelta = m_mousePosition - m_lastFrameMousePosition;
	m_mousePositionDelta.Y = -m_mousePositionDelta.Y;
	m_lastFrameMousePosition = m_mousePosition;
	ClearResults();
	glfwPollEvents();
}

void InputManager::ClearResults()
{
	m_pressedKeys.resize(0);
	m_releasedKeys.resize(0);

	m_pressedMouseButtons.resize(0);
	m_releasedMouseButtons.resize(0);
}

bool InputManager::GetKey(int key) const
{
	return std::find(m_heldKeys.begin(), m_heldKeys.end(), key) != m_heldKeys.end();
}

bool InputManager::GetKeyDown(int key) const
{
	return std::find(m_pressedKeys.begin(), m_pressedKeys.end(), key) != m_pressedKeys.end();
}

bool InputManager::GetKeyUp(int key) const
{
	return std::find(m_releasedKeys.begin(), m_releasedKeys.end(), key) != m_releasedKeys.end();
}

bool InputManager::GetMouseButton(int button) const
{
	return std::find(m_heldMouseButtons.begin(), m_heldMouseButtons.end(), button) != m_heldMouseButtons.end();
}

bool InputManager::GetMouseButtonDown(int button) const
{
	return std::find(m_pressedMouseButtons.begin(), m_pressedMouseButtons.end(), button) != m_pressedMouseButtons.end();
}

bool InputManager::GetMouseButtonUp(int button) const
{
	return std::find(m_releasedMouseButtons.begin(), m_releasedMouseButtons.end(), button) != m_releasedMouseButtons.end();
}

Vector2 InputManager::GetMouseDelta() const
{
	return m_mousePositionDelta;
}

Vector2 InputManager::GetMousePosition() const
{
	return m_mousePosition;
}

void InputManager::KeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		m_heldKeys.push_back(key);
		m_pressedKeys.push_back(key);
	}
	else if (action == GLFW_RELEASE)
	{
		m_releasedKeys.push_back(key);

		auto result = std::find(m_heldKeys.begin(), m_heldKeys.end(), key);
		if (result != m_heldKeys.end())
		{
			m_heldKeys.erase(result);
		}
	}
}

void InputManager::CursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
{
	m_mousePosition.X = (float)xpos;
	m_mousePosition.Y = (float)ypos;
}

void InputManager::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		m_heldMouseButtons.push_back(button);
		m_pressedMouseButtons.push_back(button);
	}
	else if (action == GLFW_RELEASE)
	{
		m_releasedMouseButtons.push_back(button);

		auto result = std::find(m_heldMouseButtons.begin(), m_heldMouseButtons.end(), button);
		if (result != m_heldMouseButtons.end())
		{
			m_heldMouseButtons.erase(result);
		}
	}
}

void InputManager::DebugKeyboardInput() const
{	
	system("cls");

	std::cout << "Held Keys: " << std::endl;
	for (unsigned int i = 0; i < m_heldKeys.size(); i++)
	{
		if (i != 0) std::cout << ", ";
		std::cout << m_heldKeys[i];
	}
	std::cout << std::endl;

	std::cout << "Pressed Keys: " << std::endl;
	for (unsigned int i = 0; i < m_pressedKeys.size(); i++)
	{
		if (i != 0) std::cout << ", ";
		std::cout << m_pressedKeys[i];
	}
	std::cout << std::endl;

	std::cout << "Released Keys: " << std::endl;
	for (unsigned int i = 0; i < m_releasedKeys.size(); i++)
	{
		if (i != 0) std::cout << ", ";
		std::cout << m_releasedKeys[i];
	}
	std::cout << std::endl;
}

void InputManager::DebugMouseInput() const
{
	system("cls");

	std::cout << "Mouse Position: X: " << m_mousePosition.X << ", Y: " << m_mousePosition.Y << std::endl;
	std::cout << "Mouse Delta: X: " << m_mousePositionDelta.X << ", Y: " << m_mousePositionDelta.Y << std::endl;

	std::cout << "Held Buttons: " << std::endl;
	for (unsigned int i = 0; i < m_heldMouseButtons.size(); i++)
	{
		if (i != 0) std::cout << ", ";
		std::cout << m_heldMouseButtons[i];
	}
	std::cout << std::endl;

	std::cout << "Pressed Buttons: " << std::endl;
	for (unsigned int i = 0; i < m_pressedMouseButtons.size(); i++)
	{
		if (i != 0) std::cout << ", ";
		std::cout << m_pressedMouseButtons[i];
	}
	std::cout << std::endl;

	std::cout << "Released Buttons: " << std::endl;
	for (unsigned int i = 0; i < m_releasedMouseButtons.size(); i++)
	{
		if (i != 0) std::cout << ", ";
		std::cout << m_releasedMouseButtons[i];
	}
	std::cout << std::endl;
}
