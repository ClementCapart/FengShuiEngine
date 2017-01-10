#include "FengShuiEngine_PCH.h"
#include "ShaderManager.h"
#include <iostream>
#include <iosfwd>
#include <fstream>
#include <vector>

DEFINE_SINGLETON(ShaderManager)

ShaderManager::ShaderManager()
{

}

ShaderManager::~ShaderManager()
{

}

GLuint ShaderManager::LoadShader(const char* vertexFile, const char* fragmentFile)
{
	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	if (CompileShader(vertexFile, vertexShaderID) && CompileShader(fragmentFile, fragmentShaderID))
	{
		GLuint programId = LinkShaderProgram(vertexShaderID, fragmentShaderID);
		if (programId != 0)
		{
			m_linkedPrograms.push_back(programId);
			return programId;
		}
	}

	return 0;	
}

GLuint ShaderManager::GetProgram(unsigned int index) const
{
	if (m_linkedPrograms.size() > index)
	{
		return m_linkedPrograms[index]; 
	}

	return 0;
}

bool ShaderManager::ParseShaderCode(const char* filePath, std::string& shaderCode) const
{
	shaderCode = "";
	std::ifstream shaderStream(filePath, std::ios::in);

	if (shaderStream.is_open())
	{
		std::string line = "";
		while (getline(shaderStream, line))
		{
			shaderCode += "\n" + line;
		}
		shaderStream.close();
	}
	else
	{
		printf("Impossible to open %s. Are you in the right directory ?\n", filePath);
		getchar();
		return false;
	}

	return true;
}

bool ShaderManager::CompileShader(const char* filePath, GLuint shaderID) const
{
	std::string shaderCode;

	if (ParseShaderCode(filePath, shaderCode))
	{
		GLint result = GL_FALSE;
		int infoLogLength; 

		printf("Compiling shader : %s...\n", filePath);
		const char * sourcePointer = shaderCode.c_str();
		glShaderSource(shaderID, 1, &sourcePointer, NULL);
		glCompileShader(shaderID);

		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);

		if (infoLogLength > 0)
		{
			std::vector<char> shaderErrorMessage(infoLogLength + 1);
			glGetShaderInfoLog(shaderID, infoLogLength, NULL, &shaderErrorMessage[0]);
			printf("%s\n", &shaderErrorMessage[0]);

			return false;
		}

		printf("%s compiled successfully!\n\n", filePath);
		return true;
	}
	else
	{
		return false;
	}
}

GLuint ShaderManager::LinkShaderProgram(const GLuint vertexShaderID, const GLuint fragmentShaderID) const
{
	printf("Linking program...\n");

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	GLint result = GL_FALSE;
	int infoLogLength = 0;

	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if (infoLogLength > 0)
	{
		std::vector<char> programErrorMessage(infoLogLength + 1);
		glGetProgramInfoLog(programID, infoLogLength, NULL, &programErrorMessage[0]);
		printf("%s\n", &programErrorMessage[0]);

		glDeleteProgram(programID);
		return 0;
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);

	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);

	printf("Linking completed succesfully!\n\n");

	return programID;
}
