#include "FengShuiEngine_PCH.h"
#include "DataLoader.h"
#include <stdio.h>

DEFINE_SINGLETON(DataLoader)

DataLoader::DataLoader()
{

}

DataLoader::~DataLoader()
{

}

GLuint DataLoader::LoadBMP(const char* filePath)
{
	unsigned char header[54];
	unsigned int dataPos;
	unsigned int imageWidth, imageHeight;
	unsigned int imageSize;
	unsigned char* data;

	FILE* file;
	fopen_s(&file, filePath, "rb");
	if (file == nullptr)
	{
		printf("File at %s could not be opened\n", filePath);
		return 0;
	}

	if (fread(header, 1, 54, file) != 54)
	{
		printf("File at %s is not a BMP file\n", filePath);
		return 0;
	}

	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("File at %s is not a BMP file\n", filePath);
		return 0;
	}

	dataPos = *(int*)&(header[10]);
	imageSize = *(int*)&(header[34]);
	imageWidth = *(int*)&(header[18]);
	imageHeight = *(int*)&(header[22]);

	if (imageSize == 0)
	{
		imageSize = imageWidth * imageHeight * 3;
	}

	if (dataPos == 0)
	{
		dataPos = 54;
	}

	data = new unsigned char[imageSize];

	fread(data, 1, imageSize, file);
	fclose(file);

	GLuint textureID;

	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imageWidth, imageHeight, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	return textureID;
}
