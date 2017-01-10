#pragma once

class Window
{
public:
	Window() {}
	virtual ~Window() {}
	virtual bool Init(int width, int height, char* windowName) { return false; };
	virtual bool ShouldClose() const { return true; }
	virtual void SwapBuffers() {};
};