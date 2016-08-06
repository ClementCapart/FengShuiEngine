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

private:
	Matrix m_cameraMatrix;
};