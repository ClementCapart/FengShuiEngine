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
#include "ShaderManager.h"
#include "FengShuiEngine.h"
#include "DataLoader.h"
#include "Renderer\GLRenderer.h"

Game::~Game()
{
	delete m_currentWorld;
}

// Our vertices. Three consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
static GLfloat g_vertex_buffer_data[] = {
	-1.0f, -1.0f, -1.0f, // triangle 1 : begin
	-1.0f, -1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f, -1.0f, // triangle 2 : begin
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f, // triangle 2 : end
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, -1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, -1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, -1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, -1.0f, 1.0f
};

static const GLfloat g_uv_buffer_data[] = {
	0.000059f, 1.0f - 0.000004f,
	0.000103f, 1.0f - 0.336048f,
	0.335973f, 1.0f - 0.335903f,
	1.000023f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.336024f, 1.0f - 0.671877f,
	0.667969f, 1.0f - 0.671889f,
	1.000023f, 1.0f - 0.000013f,
	0.668104f, 1.0f - 0.000013f,
	0.667979f, 1.0f - 0.335851f,
	0.000059f, 1.0f - 0.000004f,
	0.335973f, 1.0f - 0.335903f,
	0.336098f, 1.0f - 0.000071f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.336024f, 1.0f - 0.671877f,
	1.000004f, 1.0f - 0.671847f,
	0.999958f, 1.0f - 0.336064f,
	0.667979f, 1.0f - 0.335851f,
	0.668104f, 1.0f - 0.000013f,
	0.335973f, 1.0f - 0.335903f,
	0.667979f, 1.0f - 0.335851f,
	0.335973f, 1.0f - 0.335903f,
	0.668104f, 1.0f - 0.000013f,
	0.336098f, 1.0f - 0.000071f,
	0.000103f, 1.0f - 0.336048f,
	0.000004f, 1.0f - 0.671870f,
	0.336024f, 1.0f - 0.671877f,
	0.000103f, 1.0f - 0.336048f,
	0.336024f, 1.0f - 0.671877f,
	0.335973f, 1.0f - 0.335903f,
	0.667969f, 1.0f - 0.671889f,
	1.000004f, 1.0f - 0.671847f,
	0.667979f, 1.0f - 0.335851f
};

static const GLfloat g_color_buffer_data[] = {
	0.583f, 0.771f, 0.014f,
	0.609f, 0.115f, 0.436f,
	0.327f, 0.483f, 0.844f,
	0.822f, 0.569f, 0.201f,
	0.435f, 0.602f, 0.223f,
	0.310f, 0.747f, 0.185f,
	0.597f, 0.770f, 0.761f,
	0.559f, 0.436f, 0.730f,
	0.359f, 0.583f, 0.152f,
	0.483f, 0.596f, 0.789f,
	0.559f, 0.861f, 0.639f,
	0.195f, 0.548f, 0.859f,
	0.014f, 0.184f, 0.576f,
	0.771f, 0.328f, 0.970f,
	0.406f, 0.615f, 0.116f,
	0.676f, 0.977f, 0.133f,
	0.971f, 0.572f, 0.833f,
	0.140f, 0.616f, 0.489f,
	0.997f, 0.513f, 0.064f,
	0.945f, 0.719f, 0.592f,
	0.543f, 0.021f, 0.978f,
	0.279f, 0.317f, 0.505f,
	0.167f, 0.620f, 0.077f,
	0.347f, 0.857f, 0.137f,
	0.055f, 0.953f, 0.042f,
	0.714f, 0.505f, 0.345f,
	0.783f, 0.290f, 0.734f,
	0.722f, 0.645f, 0.174f,
	0.302f, 0.455f, 0.848f,
	0.225f, 0.587f, 0.040f,
	0.517f, 0.713f, 0.338f,
	0.053f, 0.959f, 0.120f,
	0.393f, 0.621f, 0.362f,
	0.673f, 0.211f, 0.457f,
	0.820f, 0.883f, 0.371f,
	0.982f, 0.099f, 0.879f
};

static GLuint vertexBuffer = 0;
static GLuint colorBuffer = 0;
static GLuint uvBuffer = 0;
static GLuint textureID = 0;

void Game::Init(Window* window)
{
	m_currentWindow = window;

	if (m_renderer != nullptr)
	{
		delete m_renderer;
	}

#if DIRECTX
	m_renderer = new DXRenderer();
#else
	m_renderer = new GLRenderer();
#endif

	m_renderer->SetClearColor(0.39f, 0.58f, 0.93f, 1.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);	

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	glGenBuffers(1, &uvBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data), g_uv_buffer_data, GL_STATIC_DRAW);

	m_camera = new Camera();
	m_cameraPosition = Vector3(0.0f, 0.0f, -5.0f);
	m_camera->SetPosition(m_cameraPosition);
	//m_camera->SetLookDirection(Vector3::Forward, Vector3::Up);
	m_camera->SetLookAtPosition(Vector3::Zero, Vector3::Up);
	m_camera->SetPerspective(60.0f, (float)FengShuiEngine::GetInstance()->GetWindowWidth() / (float) FengShuiEngine::GetInstance()->GetWindowHeight(), 0.1f, 1000.0f);

	textureID = DataLoader::GetInstance()->LoadBMP("Data/Textures/Cube.bmp");
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
	float moveSpeed = 0.1f;

	if (InputManager::GetInstance()->GetKey(GLFW_KEY_UP))
	{
		m_cameraPosition += m_camera->GetViewMatrix().GetColumn(2) * moveSpeed;
	}
	else if (InputManager::GetInstance()->GetKey(GLFW_KEY_DOWN))
	{
		m_cameraPosition -= m_camera->GetViewMatrix().GetColumn(2) * moveSpeed;
	}

	if (InputManager::GetInstance()->GetKey(GLFW_KEY_RIGHT))
	{
		m_cameraPosition += m_camera->GetDirection().Cross(m_camera->GetUp()) * moveSpeed;
	}
	else if (InputManager::GetInstance()->GetKey(GLFW_KEY_LEFT))
	{
		m_cameraPosition -= m_camera->GetDirection().Cross(m_camera->GetUp()) * moveSpeed;
	}

	if (InputManager::GetInstance()->GetKeyDown(GLFW_KEY_SPACE))
	{
		m_cameraPosition = -m_cameraPosition;
	}	

	m_camera->Update(0.0f);
}

void Game::Render()
{
	m_renderer->Clear();

	GLuint shaderProgramID = ShaderManager::GetInstance()->GetProgram(0);
	
	glEnable(GL_DEPTH_TEST);
	glUseProgram(shaderProgramID);

	Matrix modelMatrix;
	modelMatrix.SetIdentity();
	modelMatrix.SetTranslation(Vector3(0.0f, 0.0f, 15.0f));

	Matrix mvp = m_camera->GetProjectionMatrix() * modelMatrix;

	GLuint mvpID = glGetUniformLocation(shaderProgramID, "MVP");
	glUniformMatrix4fv(mvpID, 1, GL_FALSE, mvp.GetFirstMatrixElement());
	
	GLuint textureSamplerID = glGetUniformLocation(shaderProgramID, "TextureSampler");
	glUniform1i(textureSamplerID, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

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

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		(void*)0
		);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
	glVertexAttribPointer(
		2,
		2,
		GL_FLOAT,
		GL_TRUE,
		0,
		(void*)0
		);

	glDrawArrays(GL_TRIANGLES, 0, 3 * 12);

	glDisableVertexAttribArray(0);
}