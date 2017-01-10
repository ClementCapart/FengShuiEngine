#pragma once
#include "Vector3.h"

class World;
class Camera;
class Window;
class Renderer;

class Game
{
public:
	Game() : m_currentWindow(nullptr), m_currentWorld(nullptr) {}
	~Game();

	virtual void Init(Window* window);
	virtual void Load();
	virtual void Stop();
	virtual void Unload();
	virtual void Update();
	virtual void Render();

private:
	Window* m_currentWindow;
	Renderer* m_renderer;
	World* m_currentWorld;

	Camera* m_camera;
	Vector3 m_cameraPosition;
};