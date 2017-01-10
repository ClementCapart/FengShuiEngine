#include "FengShuiEngine_PCH.h"
#include "FengShuiEngine.h"
#include <string>
#include "Game.h"
#include "InputManager.h"
#include "ShaderManager.h"

#if DIRECTX
#include "Window/DXWindow.h"
#else
#include "Window/GLWindow.h"
#endif

DEFINE_SINGLETON(FengShuiEngine)

FengShuiEngine::FengShuiEngine()
	: m_window(nullptr), m_state(State::NotInitialized)
{
}

FengShuiEngine::~FengShuiEngine()
{
	if (m_state == State::Initialized || m_state == State::Running)
	{
		Quit();
	}
}

bool FengShuiEngine::Init(Settings settings)
{			
	m_settings = settings;

#if DIRECTX
	m_window = new DXWindow();
#else
	m_window = new GLWindow();
#endif

	m_window->Init(m_settings.m_Width, m_settings.m_Height, m_settings.m_WindowName);

	ShaderManager::GetInstance()->LoadShader("Shaders/BaseVertexShader.shader", "Shaders/BaseFragmentShader.shader");

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

	while (!m_window->ShouldClose())
	{
		m_game->Update();

		m_game->Render();

		m_window->SwapBuffers();

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
	delete m_window;
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