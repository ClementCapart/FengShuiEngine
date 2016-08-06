#pragma once

#include "Vector3.h"

#define MATRIX_COLUMN_COUNT 4
#define MATRIX_ROW_COUNT 4

class Matrix
{
public:
	Vector3 GetTranslation() const;
	Vector3 GetEulerRotation() const;
	Vector3 GetScale() const;

	void SetIdentity();
	void SetRow(int rowIndex, Vector3 value);
	void SetColumn(int columnIndex, Vector3 value);
	void SetValue(int rowIndex, int columnIndex, float value);

	float GetValue(int rowIndex, int columnIndex) const
	{
		if (rowIndex >= 0 && rowIndex < MATRIX_ROW_COUNT && columnIndex >= 0 && columnIndex < MATRIX_COLUMN_COUNT)
		{
			return m_elements[rowIndex][columnIndex];
		}
		
		return 0.0f;
	}

	void Translate(Vector3 translation);
	void SetTranslation(Vector3 translation);

	void Scale(Vector3 scale);
	void SetScale(Vector3 scale);

	void RotateEuler(Vector3 eulerAngle);
	void LookRotation(Vector3 forward, Vector3 up);

	void operator=(const Matrix& other);
	Matrix operator*=(const Matrix& other);	

	const float* GetFirstMatrixElement() const { return &m_elements[0][0]; }

private:
	float m_elements[MATRIX_COLUMN_COUNT][MATRIX_ROW_COUNT];
};

inline Matrix operator*(Matrix left, const Matrix& right)
{
	left *= right;
	return left;
}