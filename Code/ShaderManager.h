#pragma once

#include "GL\glew.h"
#include <string>
#include <vector>

enum ShaderType
{
	Vertex,
	Fragment
};

class ShaderManager
{
private:
	ShaderManager() {}
	~ShaderManager() {}
	static ShaderManager* s_instance;
public:
	static ShaderManager* GetInstance()
	{
		if (s_instance == nullptr)
		{
			s_instance = new ShaderManager();
		}

		return s_instance;
	}
	static void DestroyInstance()
	{
		if (s_instance != nullptr)
		{
			delete s_instance;
			s_instance = nullptr;
		}
	}

public:
	GLuint LoadShader(const char* vertexFile, const char* fragmentFile);
	GLuint GetProgram(unsigned int index) const;

private:
	bool ParseShaderCode(const char* filePath, std::string& shaderCode) const;
	bool CompileShader(const char* filePath, GLuint shaderID) const;
	GLuint LinkShaderProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID) const;

	std::vector<GLuint> m_linkedPrograms;
};