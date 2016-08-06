#include "FengShuiEngine_PCH.h"
#include "FengShuiEngine.h"
#include <string>
#include <GL/glew.h>
#include <GLFW\glfw3.h>
#include "Game.h"
#include "InputManager.h"

FengShuiEngine* FengShuiEngine::s_instance = nullptr;

FengShuiEngine::~FengShuiEngine()
{
	if (m_state == State::Initialized || m_state == State::Running)
	{
		Quit();
	}
}

bool FengShuiEngine::Init(Settings settings)
{	
	if (!glfwInit())
		return false;

	if (m_window != nullptr)
	{
		glfwDestroyWindow(m_window);
	}
	
	m_settings = settings;

	m_window = glfwCreateWindow(settings.m_Width, settings.m_Height, settings.m_WindowName, NULL, NULL);

	if (m_window == nullptr)
	{
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(m_window);

	glewExperimental = true;

	if (glewInit() != GLEW_OK)
	{
		glfwTerminate();
		return false;
	}

	InputManager::GetInstance()->Init(m_window);

	m_game = new Game();

	m_game->Init(m_window);
	m_game->Load();

	m_state = State::Initialized;

	return true;
}

void FengShuiEngine::Run()
{
	m_state = State::Running;

	while (!glfwWindowShouldClose(m_window))
	{
		m_game->Update();

		m_game->Render();
		glfwSwapBuffers(m_window);

		InputManager::GetInstance()->Update();
	}

	Quit();
}

void FengShuiEngine::Quit()
{
	m_state = State::Exiting;

	m_game->Stop();
	m_game->Unload();

	delete m_game;

	glfwTerminate();
}

FengShuiEngine::Settings FengShuiEngine::ParseStartArguments(int argc, char** argv)
{
	Settings settings;

	for (int i = 0; i < argc; i++)
	{
		if (std::strcmp(argv[i], "-width") == 0)
		{
			settings.m_Width = std::atoi(argv[i + 1]);
			i++;
		}
		else if (std::strcmp(argv[i],"-height") == 0)
		{
			settings.m_Height = std::atoi(argv[i + 1]);
			i++;
		}
		else if (std::strcmp(argv[i], "-name") == 0)
		{
			settings.m_WindowName = argv[i + 1];
		}		
	}

	return settings;
}