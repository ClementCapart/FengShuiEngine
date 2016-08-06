#include "FengShuiEngine_PCH.h"
#include "Camera.h"
#include "FengShuiEngine.h"


Camera::Camera()
{
	m_projectionMatrix.SetIdentity();
	m_viewMatrix.SetIdentity();
}

void Camera::SetPosition(Vector3 position)
{
	m_viewMatrix.SetTranslation(position);
}

void Camera::SetEulerRotation(Vector3 eulerRotation)
{

}

void Camera::SetLookDirection(Vector3 forward, Vector3 up)
{
	Vector3 right = up.Cross(forward).Normalized();
	m_viewMatrix.SetColumn(0, right);
	m_viewMatrix.SetColumn(1, forward.Cross(right).Normalized());
	m_viewMatrix.SetColumn(2, forward.Normalized());
}

void Camera::SetLookAtPosition(Vector3 positionToLookAt, Vector3 up)
{
	SetLookDirection((positionToLookAt - m_viewMatrix.GetTranslation()).Normalized(), up);
}

void Camera::SetPerspective(float fov, float aspectRatio, float nearClipPlane, float farClipPlane)
{
	if (fov <= 0.0f || aspectRatio == 0)
	{
		return;
	}

	float fovRad = fov / 180.0f * M_PI;
	float tanHalfFov = std::tan(fovRad / 2.0f);
	float zRange = farClipPlane - nearClipPlane;

	m_projectionMatrix.SetIdentity();

	m_projectionMatrix.SetValue(0, 0, aspectRatio * (1.0f / tanHalfFov));
	m_projectionMatrix.SetValue(1, 1, 1.0f / tanHalfFov);
	m_projectionMatrix.SetValue(2, 2, -(farClipPlane + nearClipPlane) / zRange);
	m_projectionMatrix.SetValue(3, 2, (2.0f * farClipPlane * nearClipPlane) / zRange);
	m_projectionMatrix.SetValue(2, 3, 1.0f);
}
