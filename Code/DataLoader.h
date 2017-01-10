#pragma once

#include "HelperMacros.h"
#include "GL\glew.h"

class DataLoader
{
	DECLARE_SINGLETON(DataLoader)

public:
	GLuint LoadBMP(const char* filePath);
};