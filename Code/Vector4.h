#pragma once

#include <iostream>

class Vector4
{
public:
	Vector4() : X(0.0f), Y(0.0f), Z(0.0f), W(0.0f) {}
	Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

	float Dot(const Vector4& other) const;

	void DebugPrint() const;

	float X, Y, Z, W;
};