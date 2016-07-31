#include "Game.h"
#include <GLFW\glfw3.h>
#include <GL\GL.h>
#include "World.h"
#include "InputManager.h"

Game::~Game()
{
	delete m_currentWorld;
}

void Game::Init(GLFWwindow* window)
{
	m_currentWindow = window;
}

void Game::Load()
{

}

void Game::Unload()
{

}

void Game::Stop()
{

}

void Game::Update()
{	

}

void Game::Render()
{
	glClearColor(0.39f, 0.58f, 0.93f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}