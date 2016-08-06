#include "FengShuiEngine_PCH.h"
#include "Matrix.h"

Vector3 Matrix::GetTranslation() const
{
	return Vector3(m_elements[0][3], m_elements[1][3], m_elements[2][3]);
}

Vector3 Matrix::GetEulerRotation() const
{
	return Vector3(	std::atan2(m_elements[2][1], m_elements[2][2]), 
					std::atan2(-m_elements[2][0], std::sqrt(m_elements[2][1] * m_elements[2][1] + m_elements[2][2] * m_elements[2][2])),
					std::atan2(m_elements[1][0], m_elements[0][0])) / (float)(M_PI * 180.0f);
}

Vector3 Matrix::GetScale() const
{
	return Vector3(m_elements[0][0], m_elements[1][1], m_elements[2][2]);
}

void Matrix::SetIdentity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			m_elements[i][j] = (i == j);
		}
	}
}

void Matrix::SetRow(int rowIndex, Vector3 value)
{
	if (rowIndex >= 0 && rowIndex < MATRIX_ROW_COUNT)
	{
		m_elements[rowIndex][0] = value.X;
		m_elements[rowIndex][1] = value.Y;
		m_elements[rowIndex][2] = value.Z;
	}	
}

void Matrix::SetColumn(int columnIndex, Vector3 value)
{
	if (columnIndex >= 0 && columnIndex < MATRIX_COLUMN_COUNT)
	{
		m_elements[0][columnIndex] = value.X;
		m_elements[1][columnIndex] = value.Y;
		m_elements[2][columnIndex] = value.Z;
	}
}

void Matrix::SetValue(int rowIndex, int columnIndex, float value)
{
	if (rowIndex >= 0 && rowIndex < MATRIX_ROW_COUNT && columnIndex >= 0 && columnIndex << MATRIX_COLUMN_COUNT)
	{
		m_elements[rowIndex][columnIndex] = value;
	}
}

void Matrix::Translate(Vector3 translation)
{
	SetTranslation(GetTranslation() + translation);
}

void Matrix::SetTranslation(Vector3 translation)
{
	SetColumn(3, translation);
}

void Matrix::Scale(Vector3 scale)
{

}

void Matrix::SetScale(Vector3 scale)
{
}

void Matrix::RotateEuler(Vector3 eulerAngle)
{
	eulerAngle /= (float)(180.0f * M_PI);

	Matrix xAngle;
	xAngle.SetIdentity();
	Matrix yAngle;
	yAngle.SetIdentity();
	Matrix zAngle;
	zAngle.SetIdentity();

	xAngle.m_elements[1][1] = std::cos(eulerAngle.X);
	xAngle.m_elements[2][1] = std::sin(eulerAngle.X);
	xAngle.m_elements[1][2] = -std::sin(eulerAngle.X);
	xAngle.m_elements[2][2] = std::cos(eulerAngle.X);
	
	yAngle.m_elements[0][0] = std::cos(eulerAngle.Y);
	yAngle.m_elements[2][0] = -std::sin(eulerAngle.Y);
	yAngle.m_elements[0][2] = std::sin(eulerAngle.Y);
	yAngle.m_elements[2][2] = std::cos(eulerAngle.Y);
	
	zAngle.m_elements[0][0] = std::cos(eulerAngle.Z);
	zAngle.m_elements[1][0] = std::sin(eulerAngle.Z);
	zAngle.m_elements[0][1] = -std::sin(eulerAngle.Z);
	zAngle.m_elements[1][1] = std::cos(eulerAngle.X);

	Matrix result = zAngle * yAngle * xAngle;

	for (int i = 0; i < MATRIX_ROW_COUNT; i++)
	{
		for (int j = 0; j < MATRIX_COLUMN_COUNT; j++)
		{
			m_elements[i][j] = result.m_elements[i][j];
		}
	}
}

void Matrix::operator=(const Matrix& other)
{
	m_elements[0][0] = other.m_elements[0][0];
	m_elements[0][1] = other.m_elements[0][1];
	m_elements[0][2] = other.m_elements[0][2];
	m_elements[0][3] = other.m_elements[0][3];

	m_elements[1][0] = other.m_elements[1][0];
	m_elements[1][1] = other.m_elements[1][1];
	m_elements[1][2] = other.m_elements[1][2];
	m_elements[1][3] = other.m_elements[1][3];

	m_elements[2][0] = other.m_elements[2][0];
	m_elements[2][1] = other.m_elements[2][1];
	m_elements[2][2] = other.m_elements[2][2];
	m_elements[2][3] = other.m_elements[2][3];

	m_elements[3][0] = other.m_elements[3][0];
	m_elements[3][1] = other.m_elements[3][1];
	m_elements[3][2] = other.m_elements[3][2];
	m_elements[3][3] = other.m_elements[3][3];
}

Matrix Matrix::operator*=(const Matrix& other)
{
	m_elements[0][0] = m_elements[0][0] * other.m_elements[0][0] + m_elements[0][1] * other.m_elements[1][0] + m_elements[0][2] * m_elements[2][0] + m_elements[0][3] * m_elements[3][0];
	m_elements[0][1] = m_elements[0][0] * other.m_elements[0][1] + m_elements[0][1] * other.m_elements[1][1] + m_elements[0][2] * m_elements[2][1] + m_elements[0][3] * m_elements[3][1];
	m_elements[0][2] = m_elements[0][0] * other.m_elements[0][2] + m_elements[0][1] * other.m_elements[1][2] + m_elements[0][2] * m_elements[2][2] + m_elements[0][3] * m_elements[3][2];
	m_elements[0][3] = m_elements[0][0] * other.m_elements[0][3] + m_elements[0][1] * other.m_elements[1][3] + m_elements[0][2] * m_elements[2][3] + m_elements[0][3] * m_elements[3][3];

	m_elements[1][0] = m_elements[1][0] * other.m_elements[0][0] + m_elements[1][1] * other.m_elements[1][0] + m_elements[1][2] * m_elements[2][0] + m_elements[1][3] * m_elements[3][0];
	m_elements[1][1] = m_elements[1][0] * other.m_elements[0][1] + m_elements[1][1] * other.m_elements[1][1] + m_elements[1][2] * m_elements[2][1] + m_elements[1][3] * m_elements[3][1];
	m_elements[1][2] = m_elements[1][0] * other.m_elements[0][2] + m_elements[1][1] * other.m_elements[1][2] + m_elements[1][2] * m_elements[2][2] + m_elements[1][3] * m_elements[3][2];
	m_elements[1][3] = m_elements[1][0] * other.m_elements[0][3] + m_elements[1][1] * other.m_elements[1][3] + m_elements[1][2] * m_elements[2][3] + m_elements[1][3] * m_elements[3][3];

	m_elements[2][0] = m_elements[2][0] * other.m_elements[0][0] + m_elements[2][1] * other.m_elements[1][0] + m_elements[2][2] * m_elements[2][0] + m_elements[2][3] * m_elements[3][0];
	m_elements[2][1] = m_elements[2][0] * other.m_elements[0][1] + m_elements[2][1] * other.m_elements[1][1] + m_elements[2][2] * m_elements[2][1] + m_elements[2][3] * m_elements[3][1];
	m_elements[2][2] = m_elements[2][0] * other.m_elements[0][2] + m_elements[2][1] * other.m_elements[1][2] + m_elements[2][2] * m_elements[2][2] + m_elements[2][3] * m_elements[3][2];
	m_elements[2][3] = m_elements[2][0] * other.m_elements[0][3] + m_elements[2][1] * other.m_elements[1][3] + m_elements[2][2] * m_elements[2][3] + m_elements[2][3] * m_elements[3][3];

	m_elements[3][0] = m_elements[3][0] * other.m_elements[0][0] + m_elements[3][1] * other.m_elements[1][0] + m_elements[3][2] * m_elements[2][0] + m_elements[3][3] * m_elements[3][0];
	m_elements[3][1] = m_elements[3][0] * other.m_elements[0][1] + m_elements[3][1] * other.m_elements[1][1] + m_elements[3][2] * m_elements[2][1] + m_elements[3][3] * m_elements[3][1];
	m_elements[3][2] = m_elements[3][0] * other.m_elements[0][2] + m_elements[3][1] * other.m_elements[1][2] + m_elements[3][2] * m_elements[2][2] + m_elements[3][3] * m_elements[3][2];
	m_elements[3][3] = m_elements[3][0] * other.m_elements[0][3] + m_elements[3][1] * other.m_elements[1][3] + m_elements[3][2] * m_elements[2][3] + m_elements[3][3] * m_elements[3][3];

	return *this;
}
