#include "FengShuiEngine_PCH.h"
#include "Matrix.h"
#include <xutility>

Vector3 Matrix::GetTranslation() const
{
	return Vector3(m_Matrix[12], m_Matrix[13], m_Matrix[14]);
}

Vector3 Matrix::GetEulerRotation() const
{
	float sy = std::sqrt(m_Matrix[0] * m_Matrix[0] + m_Matrix[4] * m_Matrix[4]);
	bool singular = sy <= 1e-6;

	float x, y, z;
	if(!singular)
	{
		x = std::atan2(-m_Matrix[6], m_Matrix[10]);
		y = std::atan2(-m_Matrix[2], sy);
		z = std::atan2(m_Matrix[1], m_Matrix[0]);
	}
	else
	{
		x = std::atan2(-m_Matrix[9], m_Matrix[5]);
		y = std::atan2(-m_Matrix[2], sy);
		z = 0;
	}

	return Vector3(x, y, z) * 180.0f / M_PI;
}

Vector3 Matrix::GetScale() const
{	
	//TODO
	return Vector3(1.0f, 1.0f, 1.0f);
}

void Matrix::SetIdentity()
{
	for (int row = 0; row < 4; row++)
	{
		for (int column = 0; column < 4; column++)
		{
			m_Matrix[(row * 4) + column] = (row == column);
		}
	}
}

void Matrix::SetRow(int rowIndex, Vector4 value)
{
	if (rowIndex >= 0 && rowIndex < 4)
	{
		m_Matrix[rowIndex * 4] = value.X;
		m_Matrix[rowIndex * 4 + 1] = value.Y;
		m_Matrix[rowIndex * 4 + 2] = value.Z;
		m_Matrix[rowIndex * 4 + 3] = value.W;
	}
}

void Matrix::SetColumn(int columnIndex, Vector4 value)
{	
	if (columnIndex >= 0 && columnIndex < 4)
	{
		m_Matrix[columnIndex] = value.X;
		m_Matrix[4 + columnIndex] = value.Y;
		m_Matrix[8 + columnIndex] = value.Z;
		m_Matrix[12 + columnIndex] = value.W;
	}
}

void Matrix::SetValue(int rowIndex, int columnIndex, float value)
{
	if (rowIndex >= 0 && rowIndex < 4 && columnIndex >= 0 && columnIndex < 4)
	{
		m_Matrix[rowIndex * 4 + columnIndex] = value;
	}
}

Vector4 Matrix::GetRow(int rowIndex) const
{
	if (rowIndex >= 0 && rowIndex < 4)
	{
		return Vector4(m_Matrix[rowIndex * 4], m_Matrix[rowIndex * 4 + 1], m_Matrix[rowIndex * 4 + 2], m_Matrix[rowIndex * 4 + 3]);
	}

	return Vector4();
}

Vector4 Matrix::GetColumn(int columnIndex) const
{
	if (columnIndex >= 0 && columnIndex < 4)
	{
		return Vector4(m_Matrix[columnIndex], m_Matrix[4 + columnIndex], m_Matrix[8 + columnIndex], m_Matrix[12 + columnIndex]);
	}

	return Vector4();
}

float Matrix::GetValue(int columnIndex, int rowIndex) const
{
	if (rowIndex >= 0 && rowIndex < 4 && columnIndex >= 0 && columnIndex < 4)
	{
		return m_Matrix[rowIndex * 4 + columnIndex];
	}

	return 0.0f;
}

void Matrix::Translate(Vector3 translation)
{
	SetTranslation(GetTranslation() + translation);
}

void Matrix::SetTranslation(Vector3 translation)
{
	SetRow(3, Vector4(translation.X, translation.Y, translation.Z, 1.0f));
}

void Matrix::Scale(Vector3 scale)
{

}

void Matrix::SetScale(Vector3 scale)
{
	
}

void Matrix::RotateEuler(Vector3 eulerAngle)
{
	eulerAngle *= (float)(M_PI / 180.0f);

	Matrix xAngle;
	xAngle.SetIdentity();
	Matrix yAngle;
	yAngle.SetIdentity();
	Matrix zAngle;
	zAngle.SetIdentity();

	xAngle.m_Matrix[5] = std::cos(eulerAngle.X);
	xAngle.m_Matrix[6] = std::sin(eulerAngle.X);
	xAngle.m_Matrix[9] = -std::sin(eulerAngle.X);
	xAngle.m_Matrix[10] = std::cos(eulerAngle.X);
	
	yAngle.m_Matrix[0] = std::cos(eulerAngle.Y);
	yAngle.m_Matrix[2] = -std::sin(eulerAngle.Y);
	yAngle.m_Matrix[8] = std::sin(eulerAngle.Y);
	yAngle.m_Matrix[10] = std::cos(eulerAngle.Y);
	
	zAngle.m_Matrix[0] = std::cos(eulerAngle.Z);
	zAngle.m_Matrix[1] = std::sin(eulerAngle.Z);
	zAngle.m_Matrix[4] = -std::sin(eulerAngle.Z);
	zAngle.m_Matrix[5] = std::cos(eulerAngle.Z);

	Matrix result = zAngle * yAngle * xAngle;

	std::memcpy(m_Matrix, result.GetFirstMatrixElement(), sizeof(float) * 16);
}

void Matrix::operator=(const Matrix& other)
{
	m_Matrix[0] = other.m_Matrix[0];
	m_Matrix[1] = other.m_Matrix[1];
	m_Matrix[2] = other.m_Matrix[2];
	m_Matrix[3] = other.m_Matrix[3];
						
	m_Matrix[5] = other.m_Matrix[4];
	m_Matrix[6] = other.m_Matrix[5];
	m_Matrix[7] = other.m_Matrix[6];
	m_Matrix[8] = other.m_Matrix[7];
						
	m_Matrix[9] = other.m_Matrix[8];
	m_Matrix[10] = other.m_Matrix[9];
	m_Matrix[11] = other.m_Matrix[10];
	m_Matrix[12] = other.m_Matrix[11];
						
	m_Matrix[13] = other.m_Matrix[12];
	m_Matrix[14] = other.m_Matrix[13];
	m_Matrix[15] = other.m_Matrix[14];
	m_Matrix[16] = other.m_Matrix[15];
}

Matrix Matrix::operator*=(const Matrix& other)
{
	float matrix[16];

	matrix[0] = GetColumn(0).Dot(other.GetRow(0));
	matrix[1] = GetColumn(1).Dot(other.GetRow(0));
	matrix[2] = GetColumn(2).Dot(other.GetRow(0));
	matrix[3] = GetColumn(3).Dot(other.GetRow(0));
	matrix[4] = GetColumn(0).Dot(other.GetRow(1));
	matrix[5] = GetColumn(1).Dot(other.GetRow(1));
	matrix[6] = GetColumn(2).Dot(other.GetRow(1));
	matrix[7] = GetColumn(3).Dot(other.GetRow(1));
	matrix[8] = GetColumn(0).Dot(other.GetRow(2));
	matrix[9] = GetColumn(1).Dot(other.GetRow(2));
	matrix[10] = GetColumn(2).Dot(other.GetRow(2));
	matrix[11] = GetColumn(3).Dot(other.GetRow(2));
	matrix[12] = GetColumn(0).Dot(other.GetRow(3));
	matrix[13] = GetColumn(1).Dot(other.GetRow(3));
	matrix[14] = GetColumn(2).Dot(other.GetRow(3));
	matrix[15] = GetColumn(3).Dot(other.GetRow(3));

	std::memcpy(m_Matrix, &matrix[0], sizeof(float) * 16);

	return *this;
}

void Matrix::DebugPrint(bool transposed) const
{
	if (!transposed)
	{
		GetRow(0).DebugPrint();
		std::cout << std::endl;
		GetRow(1).DebugPrint();
		std::cout << std::endl;
		GetRow(2).DebugPrint();
		std::cout << std::endl;
		GetRow(3).DebugPrint();
		std::cout << std::endl;
	}
	else
	{
		GetColumn(0).DebugPrint();
		std::cout << std::endl;
		GetColumn(1).DebugPrint();
		std::cout << std::endl;
		GetColumn(2).DebugPrint();
		std::cout << std::endl;
		GetColumn(3).DebugPrint();
		std::cout << std::endl;
	}
}
