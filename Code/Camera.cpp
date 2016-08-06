#include "FengShuiEngine_PCH.h"
#include "Camera.h"
#include "FengShuiEngine.h"


Camera::Camera()
{
	m_projectionMatrix.SetIdentity();
	m_viewMatrix.SetIdentity();
}

void Camera::SetEulerRotation(Vector3 eulerRotation)
{

}

void Camera::SetLookDirection(Vector3 forward, Vector3 up)
{
	m_up = up;
	m_direction = forward;
}

void Camera::SetLookAtPosition(Vector3 positionToLookAt, Vector3 up)
{
	m_up = up;
	m_direction = (positionToLookAt - m_position).Normalized();
}

void Camera::SetPerspective(float fov, float aspectRatio, float nearClipPlane, float farClipPlane)
{
	if (fov <= 0.0f || aspectRatio == 0)
	{
		return;
	}

	float fovRad = fov / 180.0f * (float)M_PI;
	float tanHalfFov = std::tan(fovRad / 2.0f);
	float zRange = farClipPlane - nearClipPlane;

	m_projectionMatrix.SetIdentity();

	m_projectionMatrix.SetValue(0, 0, 1.0f / (aspectRatio * tanHalfFov));
	m_projectionMatrix.SetValue(1, 1, 1.0f / tanHalfFov);
	m_projectionMatrix.SetValue(2, 2, (farClipPlane + nearClipPlane) / zRange);
	m_projectionMatrix.SetValue(3, 2, -(2.0f * farClipPlane * nearClipPlane) / zRange);
	m_projectionMatrix.SetValue(2, 3, 1.0f);
	m_projectionMatrix.SetValue(3, 3, 0.0f);
}

const Matrix& Camera::GetViewMatrix()
{
	Vector3 right = m_up.Cross(m_direction).Normalized();
	m_viewMatrix.SetColumn(0, right);
	m_viewMatrix.SetColumn(1, m_direction.Cross(right).Normalized());
	m_viewMatrix.SetColumn(2, m_direction.Normalized());
	m_viewMatrix.SetTranslation(Vector3(-(right.Dot(m_position)), -(m_up.Dot(m_position)), -(m_direction.Dot(m_position))));

	return m_viewMatrix;
}
