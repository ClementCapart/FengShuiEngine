#pragma once

#include "FengShuiEngine_PCH.h"
#include "Vector3.h"
#include "Matrix.h"

class Camera
{
public:
	Camera();

	void SetEulerRotation(Vector3 eulerRotation);
	void SetLookDirection(Vector3 forward, Vector3 up);
	void SetLookAtPosition(Vector3 positionToLookAt, Vector3 up);

	void SetPerspective(float angle, float ratio, float nearClipPlane, float farClipPlane);

	const Matrix& GetProjectionMatrix() const { return m_projectionMatrix; }
	const Matrix& GetViewMatrix();
	Vector3 GetPosition() const { return m_position; }
	void SetPosition(Vector3 position) { m_position = position; }

	Vector3 GetDirection() const { return m_direction; }
	void SetDirection(Vector3 direction) { m_direction = direction; }

	Vector3 GetUp() const { return m_up; }
	void SetUp(Vector3 up) { m_up = up; }

	void Update(float deltaTime);
private:
	Matrix m_projectionMatrix;
	Matrix m_viewMatrix;
	Vector3 m_position;
	Vector3 m_direction;
	Vector3 m_up;
};