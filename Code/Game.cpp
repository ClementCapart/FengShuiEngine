#include "FengShuiEngine_PCH.h"
#include "Game.h"
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GL\GL.h>
#include "World.h"
#include "InputManager.h"
#include "Camera.h"
#include "Vector3.h"
#include "Quaternion.h"

Game::~Game()
{
	delete m_currentWorld;
}

static const GLfloat g_vertex_buffer_data[] =
{
	-1.0f, -1.0f, 0.0f,
	1.0f, -1.0f, 0.0f,
	0.0f, 1.0f, 0.0f,
};

static GLuint vertexBuffer = 0;

void Game::Init(GLFWwindow* window)
{
	m_currentWindow = window;

	GLuint VertexArrayID;

	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);	

	glGenBuffers(1, &vertexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	Quaternion q1(90.0f, Vector3::Up);
	Quaternion q2(45.0f, Vector3::Right);

	Quaternion q3 = q1 * q2;

	Vector3 v(1.0f, 0.0f, 0.0f);

	v = q1 * v;

	
	float angle;
	q1.ToAxisAngle(v, angle);

	v = Vector3::Zero;

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

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glDisableVertexAttribArray(0);


}