#pragma once

#include <vector>

struct GLFWwindow;

class InputManager
{
private:
	InputManager() {}
	~InputManager() {}
	static InputManager* s_instance;

	static void StaticKeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		s_instance->KeyboardKeyCallback(window, key, scancode, action, mods);
	}

	void KeyboardKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

public:
	static InputManager* GetInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new InputManager();
		}

		return s_instance;
	}
	static void DestroyInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}

public:
	void Init(GLFWwindow* window);
	void Update();	

	bool GetKey(int key) const;
	bool GetKeyDown(int key) const;
	bool GetKeyUp(int key) const;

	void ClearResults();

private:
	void DebugKeyboardInput() const;

private:
	std::vector<int> m_heldKeys;
	std::vector<int> m_pressedKeys;
	std::vector<int> m_releasedKeys;
};