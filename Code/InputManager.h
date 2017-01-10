#pragma once

#include <vector>
#include "HelperMacros.h"
#include "Window\Window.h"
#include "Vector2.h"

struct GLFWwindow;

class InputManager
{
	DECLARE_SINGLETON(InputManager)

private:
	static void StaticKeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		s_instance->KeyboardKeyCallback(window, key, scancode, action, mods);
	}

	static void StaticCursorPositionCallback(GLFWwindow* window, double xpos, double ypos)
	{
		s_instance->CursorPositionCallback(window, xpos, ypos);
	}

	static void StaticMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		s_instance->MouseButtonCallback(window, button, action, mods);
	}

	void KeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void CursorPositionCallback(GLFWwindow* window, double xpos, double ypos);
	void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

public:
	void Init(Window* window);
	void Update();	

	bool GetKey(int key) const;
	bool GetKeyDown(int key) const;
	bool GetKeyUp(int key) const;

	bool GetMouseButton(int button) const;
	bool GetMouseButtonDown(int button) const;
	bool GetMouseButtonUp(int button) const;

	Vector2 GetMouseDelta() const;
	Vector2 GetMousePosition() const;

	void ClearResults();

private:
	void DebugKeyboardInput() const;
	void DebugMouseInput() const;

private:
	std::vector<int> m_heldKeys;
	std::vector<int> m_pressedKeys;
	std::vector<int> m_releasedKeys;

	std::vector<int> m_heldMouseButtons;
	std::vector<int> m_pressedMouseButtons;
	std::vector<int> m_releasedMouseButtons;

	Vector2 m_mousePosition;
	Vector2 m_lastFrameMousePosition;
	Vector2 m_mousePositionDelta;
};