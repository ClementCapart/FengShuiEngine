#pragma once

#include "Vector3.h"

class Quaternion
{
public:

	Quaternion() : W(1.0f) {}
	Quaternion(float rotation, const Vector3& axis);
	Quaternion(float x, float y, float z, float w) : Axis(Vector3(x, y, z)), W(w) {}

	void SetIdentity();

	Quaternion Inverse() const;
	float Length() const;

	void ToAxisAngle(Vector3& outAxis, float& outAngle) const;

	//Operators
	Quaternion& operator*=(const Quaternion& other);
	Vector3 operator*(const Vector3& other) const;
	Quaternion operator^(const float& power) const;

private:
	Vector3 Axis;
	float W;

public:
	static Quaternion Slerp(const Quaternion& start, const Quaternion& end, float time);
};

inline Quaternion operator*(Quaternion left, const Quaternion& right)
{
	left *= right;
	return left;
}
