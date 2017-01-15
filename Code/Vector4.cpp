#include "FengShuiEngine_PCH.h"
#include "Vector4.h"

float Vector4::Dot(const Vector4 & other) const
{
	return X * other.X + Y * other.Y + Z * other.Z + W * other.W;
}

void Vector4::DebugPrint() const
{
	std::cout << "{ " << X << ", " << Y << ", " << Z << ", " << W << " }";
}
