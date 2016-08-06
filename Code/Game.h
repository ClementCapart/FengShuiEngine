#pragma once
#include "Vector3.h"

class World;
class Camera;
struct GLFWwindow;

class Game
{
public:
	Game() : m_currentWindow(nullptr), m_currentWorld(nullptr) {}
	~Game();

	virtual void Init(GLFWwindow* window);
	virtual void Load();
	virtual void Stop();
	virtual void Unload();
	virtual void Update();
	virtual void Render();

private:
	GLFWwindow* m_currentWindow;
	World* m_currentWorld;

	Camera* m_camera;
	Vector3 m_cameraPosition;
};