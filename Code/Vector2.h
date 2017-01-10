#pragma once

class Vector2
{
public:
	Vector2() : X(0.0f), Y(0.0f) {}
	Vector2(float x, float y) : X(x), Y(y) {}

	float X, Y;

	float   Length() const;
	float   SquaredLength() const;
	Vector2 Normalized() const;
	Vector2 Inverse() const;

	float Dot(const Vector2& other) const;

	//Operators
	Vector2& operator+= (const Vector2& other)
	{
		X += other.X;
		Y += other.Y;

		return *this;
	}

	Vector2 operator-= (const Vector2& other)
	{
		X -= other.X;
		Y -= other.Y;

		return *this;
	}

	Vector2 operator-() const
	{
		return Vector2(-X, -Y);
	}

	Vector2 operator*= (const Vector2& other)
	{
		X *= other.X;
		Y *= other.Y;

		return *this;
	}

	Vector2 operator*= (const float& other)
	{
		X *= other;
		Y *= other;

		return *this;
	}

	Vector2 operator*= (const int& other)
	{
		X *= other;
		Y *= other;

		return *this;
	}

	Vector2 operator*= (const double& other)
	{
		X *= (float)other;
		Y *= (float)other;

		return *this;
	}

	Vector2 operator/= (const float& other)
	{
		X /= other;
		Y /= other;

		return *this;
	}

	Vector2 operator/= (const int& other)
	{
		X /= other;
		Y /= other;

		return *this;
	}

	Vector2 operator/= (const double& other)
	{
		X /= (float)other;
		Y /= (float)other;

		return *this;
	}

public:
	const static Vector2 Zero;
	const static Vector2 One;
	const static Vector2 Right;
	const static Vector2 Up;

	static Vector2 Lerp(const Vector2& start, const Vector2& end, float time);
};

//Operators
inline Vector2 operator+(Vector2 left, const Vector2& right)
{
	left += right;
	return left;
}

inline Vector2 operator-(Vector2 left, const Vector2& right)
{
	left -= right;
	return left;
}

inline Vector2 operator*(Vector2 left, const Vector2& right)
{
	left *= right;
	return left;
}

inline Vector2 operator*(Vector2 left, const float& right)
{
	left *= right;
	return left;
}

inline Vector2 operator*(const float& left, Vector2 right)
{
	right *= left;
	return right;
}

inline Vector2 operator*(Vector2 left, const int& right)
{
	left *= right;
	return left;
}

inline Vector2 operator*(const int& left, Vector2 right)
{
	right *= left;
	return right;
}

inline Vector2 operator*(Vector2 left, const double& right)
{
	left *= right;
	return left;
}

inline Vector2 operator*(const double& left, Vector2 right)
{
	right *= left;
	return right;
}

inline Vector2 operator/(Vector2 left, const float& right)
{
	left /= right;
	return left;
}

inline Vector2 operator/(Vector2 left, const int& right)
{
	left /= right;
	return left;
}

inline Vector2 operator/(Vector2 left, const double& right)
{
	left /= right;
	return left;
}