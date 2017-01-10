#pragma once

#include "Window.h"

struct GLFWwindow;

class GLWindow : public Window
{
public:
	GLWindow() : m_window(nullptr) {}
	~GLWindow();

	virtual bool Init(int width, int height, char* windowName) override;
	virtual bool ShouldClose() const;

	virtual void SwapBuffers() override;

public:
	GLFWwindow* m_window;
};