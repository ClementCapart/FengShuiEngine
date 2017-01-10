#pragma once

#include "Window.h"

class DXWindow : public Window
{
public:
	virtual bool Init(int width, int height, char* windowName) override;
	virtual bool ShouldClose() const;
};