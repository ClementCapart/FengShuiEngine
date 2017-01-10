#pragma once

#include "HelperMacros.h"
#include "Window\Window.h"

class Game;
struct GLFWwindow;

class FengShuiEngine
{
public:
	enum State
	{
		NotInitialized = 0,
		Initialized,
		Running,
		Exiting,
	};

	struct Settings
	{
		Settings() : m_WindowName("Feng Shui"), m_Width(640), m_Height(480) {}

		char* m_WindowName;
		int m_Width;
		int m_Height;
	};

	DECLARE_SINGLETON(FengShuiEngine)

public:
	bool Init(Settings settings = Settings());
	void Run();
	void Quit();

	int GetWindowWidth() const { return m_settings.m_Width; }
	int GetWindowHeight() const { return m_settings.m_Height; }

	Settings ParseStartArguments(int argc, char** argv);
private:
	Window* m_window;
	Game* m_game;
	Settings m_settings;
	State m_state;
};