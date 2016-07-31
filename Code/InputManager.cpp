#include "InputManager.h"

#include <GLFW\glfw3.h>
#include <algorithm>
#include <iostream>

InputManager* InputManager::s_instance = nullptr;

void InputManager::Init(GLFWwindow* window)
{
	glfwSetKeyCallback(window, &InputManager::StaticKeyboardKeyCallback);
}

void InputManager::Update()
{	
	//DebugKeyboardInput();

	ClearResults();
	glfwPollEvents();
}

void InputManager::ClearResults()
{
	m_pressedKeys.resize(0);
	m_releasedKeys.resize(0);
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

void InputManager::DebugKeyboardInput() const
{
	system("cls");

	std::cout << "Held Keys: " << std::endl;
	for (int i = 0; i < m_heldKeys.size(); i++)
	{
		if (i != 0) std::cout << ", ";
		std::cout << m_heldKeys[i];
	}
	std::cout << std::endl;

	std::cout << "Pressed Keys: " << std::endl;
	for (int i = 0; i < m_pressedKeys.size(); i++)
	{
		if (i != 0) std::cout << ", ";
		std::cout << m_pressedKeys[i];
	}
	std::cout << std::endl;

	std::cout << "Released Keys: " << std::endl;
	for (int i = 0; i < m_releasedKeys.size(); i++)
	{
		if (i != 0) std::cout << ", ";
		std::cout << m_releasedKeys[i];
	}
	std::cout << std::endl;
}