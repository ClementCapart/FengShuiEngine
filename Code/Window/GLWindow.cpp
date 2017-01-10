#include "FengShuiEngine_PCH.h"
#include "GLWindow.h"
#include <GL/glew.h>
#include "GLFW/glfw3.h"

bool GLWindow::Init(int width, int height, char* windowName)
{
	if (!glfwInit())
		return false;

	if (m_window != nullptr)
	{
		glfwDestroyWindow(m_window);
	}

	m_window = glfwCreateWindow(width, height, windowName, NULL, NULL);

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

	return true;
}

GLWindow::~GLWindow()
{
	glfwDestroyWindow(m_window);
	glfwTerminate();
}

bool GLWindow::ShouldClose() const
{
	return glfwWindowShouldClose(m_window) != 0;
}

void GLWindow::SwapBuffers()
{
	glfwSwapBuffers(m_window);
}

