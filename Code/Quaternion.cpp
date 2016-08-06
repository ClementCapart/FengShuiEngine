#include "FengShuiEngine_PCH.h"
#include "Quaternion.h"

Quaternion::Quaternion(float rotation, const Vector3& axis)
{
	//To radians
	rotation = rotation / 180.0f * (float)M_PI;

	Axis = axis * std::sin(rotation / 2.0f);
	W = std::cos(rotation / 2.0f);

	std::cout << "Length : " << Length() << std::endl;
}

void Quaternion::SetIdentity()
{
	Axis = Vector3::Zero;
	W = 1.0f;
}

Quaternion Quaternion::Inverse() const
{
	return Quaternion(-Axis.X, -Axis.Y, -Axis.Z, W);
}

float Quaternion::Length() const
{
	return std::sqrt(Axis.SquaredLength() + W * W);
}

void Quaternion::ToAxisAngle(Vector3& outAxis, float& outAngle) const
{
	if (Axis.SquaredLength() < 0.00001f)
	{
		outAxis = Vector3::Right;
	}
	else
	{
		outAxis = Axis.Normalized();
	}

	outAngle = acos(W) * 2.0f;
	outAngle *= 180.0f / (float)M_PI;
}

Quaternion& Quaternion::operator*=(const Quaternion& other)
{
	W = W * other.W - Axis.Dot(other.Axis);
	Axis = (other.W * Axis) + (W * other.Axis) + Axis.Cross(other.Axis);
	return *this;
}

Vector3 Quaternion::operator*(const Vector3& other) const
{
	Vector3 crossOther = Axis.Cross(other);
	return other + crossOther * (2.0f * W) + Axis.Cross(crossOther) * 2.0f;
}

Quaternion Quaternion::operator^(const float& power) const
{
	float angle;
	Vector3 axis;

	ToAxisAngle(axis, angle);

	return Quaternion(angle * power, axis);
}

Quaternion Quaternion::Slerp(const Quaternion& start, const Quaternion& end, float time)
{
	Quaternion result;

	float flCosOmega = start.W * end.W + end.Axis.Dot(start.Axis);
	if (flCosOmega < 0.0f)
	{
		result.W = -end.W;
		result.Axis = -end.Axis;
		flCosOmega = -flCosOmega;
	}
	else
	{
		result.W = end.W;
		result.Axis = end.Axis;
	}

	float k0, k1;

	if (flCosOmega > 0.9999f)
	{
		k0 = 1.0f - time;
		k1 = time;
	}
	else
	{
		float flSinOmega = sqrt(1.0f - flCosOmega * flCosOmega);

		float flOmega = atan2(flSinOmega, flCosOmega);
		float flOneOverSinOmega = 1.0f / flSinOmega;

		k0 = sin((1.0f - time) * flOmega) * flOneOverSinOmega;
		k1 = sin(time * flOmega) * flOneOverSinOmega;
	}

	result.W = start.W * k0 + result.W * k1;
	result.Axis = start.Axis * k0 + result.Axis * k1;

	return result;
}
