#pragma once

class Renderer
{
public:
	Renderer() {};
	virtual ~Renderer() {};

	virtual void Clear() {};
	virtual void PreRender() {};
	virtual void Render() {};
	virtual void PostRender() {};

	virtual void SetClearColor(float r, float g, float b, float a) {};
};