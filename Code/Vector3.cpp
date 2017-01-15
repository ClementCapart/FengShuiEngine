#include "FengShuiEngine_PCH.h"
#include "Vector3.h"
#include <cmath>

float Vector3::Length() const
{
	return sqrt(SquaredLength());
}

float Vector3::SquaredLength() const
{
	return (X * X) + (Y * Y) + (Z * Z);
}

Vector3 Vector3::Normalized() const
{
	float length = Length();
	return *this / length;
}

Vector3 Vector3::Inverse() const
{
	return Vector3(-X, -Y, -Z);
}

float Vector3::Dot(const Vector3& other) const
{
	return X * other.X + Y * other.Y + Z * other.Z;
}

Vector3 Vector3::Cross(const Vector3& other) const
{
	return Vector3(Y * other.Z - Z * other.Y, Z * other.X - X * other.Z, X * other.Y - Y * other.X);
}

void Vector3::DebugPrint() const
{
	std::cout << "{ " << X << ", " << Y << ", " << Z << " }" << std::endl;
}

/////////////////////////////////////

//Static
const Vector3 Vector3::Zero = Vector3(0.0f, 0.0f, 0.0f);
const Vector3 Vector3::One = Vector3(1.0f, 1.0f, 1.0f);
const Vector3 Vector3::Right = Vector3(1.0f, 0.0f, 0.0f);
const Vector3 Vector3::Forward = Vector3(0.0f, 0.0f, 1.0f);
const Vector3 Vector3::Up = Vector3(0.0f, 1.0f, 0.0f);

Vector3 Vector3::Lerp(const Vector3& start, const Vector3& end, float time)
{
	return start + (end - start) * time;
}
