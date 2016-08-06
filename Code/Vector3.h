#pragma once

class Vector3
{
public:
	Vector3() : X(0.0f), Y(0.0f), Z(0.0f) {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}

	float X, Y, Z;

	float   Length() const;
	float   SquaredLength() const;
	Vector3 Normalized() const;
	Vector3 Inverse() const;

	float Dot(const Vector3& other) const;
	Vector3 Cross(const Vector3& other) const;

	//Operators
	Vector3& operator+= (const Vector3& other)
	{
		X += other.X;
		Y += other.Y;
		Z += other.Z;

		return *this;
	}

	Vector3 operator-= (const Vector3& other)
	{
		X -= other.X;
		Y -= other.Y;
		Z -= other.Z;

		return *this;
	}

	Vector3 operator-() const
	{
		return Vector3(-X, -Y, -Z);
	}

	Vector3 operator*= (const Vector3& other)
	{
		X *= other.X;
		Y *= other.Y;
		Z *= other.Z;

		return *this;
	}

	Vector3 operator*= (const float& other)
	{
		X *= other;
		Y *= other;
		Z *= other;

		return *this;
	}

	Vector3 operator*= (const int& other)
	{
		X *= other;
		Y *= other;
		Z *= other;

		return *this;
	}

	Vector3 operator*= (const double& other)
	{
		X *= (float)other;
		Y *= (float)other;
		Z *= (float)other;

		return *this;
	}

	Vector3 operator/= (const float& other)
	{
		X /= other;
		Y /= other;
		Z /= other;

		return *this;
	}

	Vector3 operator/= (const int& other)
	{
		X /= other;
		Y /= other;
		Z /= other;

		return *this;
	}

	Vector3 operator/= (const double& other)
	{
		X /= (float)other;
		Y /= (float)other;
		Z /= (float)other;

		return *this;
	}

public:
	const static Vector3 Zero;
	const static Vector3 One;
	const static Vector3 Right;
	const static Vector3 Forward;
	const static Vector3 Up;

	static Vector3 Lerp(const Vector3& start, const Vector3& end, float time);
};

//Operators
inline Vector3 operator+(Vector3 left, const Vector3& right)
{
	left += right;
	return left;
}

inline Vector3 operator-(Vector3 left, const Vector3& right)
{
	left -= right;
	return left;
}

inline Vector3 operator*(Vector3 left, const Vector3& right)
{
	left *= right;
	return left;
}

inline Vector3 operator*(Vector3 left, const float& right)
{
	left *= right;
	return left;
}

inline Vector3 operator*(const float& left, Vector3 right)
{
	right *= left;
	return right;
}

inline Vector3 operator*(Vector3 left, const int& right)
{
	left *= right;
	return left;
}

inline Vector3 operator*(const int& left, Vector3 right)
{
	right *= left;
	return right;
}

inline Vector3 operator*(Vector3 left, const double& right)
{
	left *= right;
	return left;
}

inline Vector3 operator*(const double& left, Vector3 right)
{
	right *= left;
	return right;
}

inline Vector3 operator/(Vector3 left, const float& right)
{
	left /= right;
	return left;
}

inline Vector3 operator/(Vector3 left, const int& right)
{
	left /= right;
	return left;
}

inline Vector3 operator/(Vector3 left, const double& right)
{
	left /= right;
	return left;
}