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

	void Translate(Vector3 translation);
	void SetTranslation(Vector3 translation);

	void Scale(Vector3 scale);
	void SetScale(Vector3 scale);

	void RotateEuler(Vector3 eulerAngle);
	void LookRotation(Vector3 forward, Vector3 up);

	void operator=(const Matrix& other);
	Matrix operator*=(const Matrix& other);	

private:
	float m_elements[MATRIX_COLUMN_COUNT][MATRIX_ROW_COUNT];
};

inline Matrix operator*(Matrix left, const Matrix& right)
{
	left *= right;
	return left;
}