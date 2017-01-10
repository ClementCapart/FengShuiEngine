#include "FengShuiEngine_PCH.h"
#include "GLRenderer.h"
#include "GL\glew.h"

GLRenderer::GLRenderer()
{

}

GLRenderer::~GLRenderer()
{

}

void GLRenderer::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GLRenderer::PreRender()
{

}

void GLRenderer::Render()
{

}

void GLRenderer::PostRender()
{

}

void GLRenderer::SetClearColor(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
}
