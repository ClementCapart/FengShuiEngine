#pragma once

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

private:
	FengShuiEngine()
		: m_window(nullptr), m_state(State::NotInitialized)
	{}
	~FengShuiEngine();

	static FengShuiEngine* s_instance;

public:
	static FengShuiEngine* GetInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new FengShuiEngine();
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

	bool Init(Settings settings = Settings());
	void Run();
	void Quit();

	Settings ParseStartArguments(int argc, char** argv);
private:
	GLFWwindow* m_window;
	Game* m_game;
	Settings m_settings;
	State m_state;
};