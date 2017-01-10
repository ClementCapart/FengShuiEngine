#include "FengShuiEngine_PCH.h"
#include "Vector2.h"
#include <cmath>

float Vector2::Length() const
{
	return sqrt(SquaredLength());
}

float Vector2::SquaredLength() const
{
	return (X * X) + (Y * Y);
}

Vector2 Vector2::Normalized() const
{
	float length = Length();
	return *this / length;
}

Vector2 Vector2::Inverse() const
{
	return Vector2(-X, -Y);
}

float Vector2::Dot(const Vector2& other) const
{
	return X * other.X + Y * other.Y;
}

/////////////////////////////////////

//Static
const Vector2 Vector2::Zero = Vector2(0.0f, 0.0f);
const Vector2 Vector2::One = Vector2(1.0f, 1.0f);
const Vector2 Vector2::Right = Vector2(1.0f, 0.0f);
const Vector2 Vector2::Up = Vector2(0.0f, 1.0f);

Vector2 Vector2::Lerp(const Vector2& start, const Vector2& end, float time)
{
	return start + (end - start) * time;
}
