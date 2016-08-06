#pragma once

#include "FengShuiEngine_PCH.h"
#include "Vector3.h"
#include "Matrix.h"

class Camera
{
public:
	Camera() {}

	void SetPosition(Vector3 position);
	void SetEulerRotation(Vector3 eulerRotation);
	void SetLookDirection(Vector3 forward, Vector3 up);
	void SetLookAtPosition(Vector3 positionToLookAt);

	void SetPerspective(float angle, float ratio, float nearClipPlane, float farClipPlane);

	const Matrix& GetProjectionMatrix() const { return m_projectionMatrix; }
	const Matrix& GetViewMatrix() const { return m_viewMatrix; }

private:
	Matrix m_projectionMatrix;
	Matrix m_viewMatrix;
};