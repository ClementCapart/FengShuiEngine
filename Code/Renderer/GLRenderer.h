#pragma once

#include "Renderer/Renderer.h"

class GLRenderer : public Renderer
{
public:
	GLRenderer();
	virtual ~GLRenderer();

	virtual void Clear() override;
	virtual void PreRender() override;
	virtual void Render() override;
	virtual void PostRender() override;

	virtual void SetClearColor(float r, float g, float b, float a) override;
};