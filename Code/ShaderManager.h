#pragma once

#include "GL\glew.h"
#include <string>
#include <vector>
#include "HelperMacros.h"

enum ShaderType
{
	Vertex,
	Fragment
};

class ShaderManager
{
	DECLARE_SINGLETON(ShaderManager)

public:
	GLuint LoadShader(const char* vertexFile, const char* fragmentFile);
	GLuint GetProgram(unsigned int index) const;

private:
	bool ParseShaderCode(const char* filePath, std::string& shaderCode) const;
	bool CompileShader(const char* filePath, GLuint shaderID) const;
	GLuint LinkShaderProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID) const;

	std::vector<GLuint> m_linkedPrograms;
};