#pragma once

class Vector4
{
public:
	Vector4() : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) {}
	Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

	float X, Y, Z, W;
};