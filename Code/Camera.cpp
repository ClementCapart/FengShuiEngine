#include "FengShuiEngine_PCH.h"
#include "Camera.h"
#include "FengShuiEngine.h"
#include "Quaternion.h"
#include "InputManager.h"

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

	float zRange = farClipPlane - nearClipPlane;

	float top = nearClipPlane * std::tan(((float)M_PI / 180) * (fov / 2.0f));
	float bottom = -top;
	float right = top * aspectRatio;
	float left = -right;

	m_projectionMatrix.SetIdentity();
	m_projectionMatrix.SetValue(0, 0, (2 * nearClipPlane) / (right - left));
	m_projectionMatrix.SetValue(1, 1, (2 * nearClipPlane) / (top - bottom));
	m_projectionMatrix.SetValue(2, 2, -(farClipPlane + nearClipPlane) / zRange);
	m_projectionMatrix.SetValue(2, 3, -1.0f);
	m_projectionMatrix.SetValue(3, 2, -(2 * farClipPlane * nearClipPlane) / zRange);
	m_projectionMatrix.SetValue(3, 3, 0.0f);
}

const Matrix& Camera::GetViewMatrix()
{
	Vector3 right = m_up.Cross(m_direction).Normalized();
	Vector3 up = m_direction.Cross(right).Normalized();
	m_viewMatrix.SetColumn(0, Vector4(right.X, right.Y, right.Z, 0.0f));
	m_viewMatrix.SetColumn(1, Vector4(up.X, up.Y, up.Z, 0.0f));
	m_viewMatrix.SetColumn(2, Vector4(m_direction.X, m_direction.Y, m_direction.Z, 0.0f));
	m_viewMatrix.SetTranslation(Vector3(-(right.Dot(m_position)), -(m_up.Dot(m_position)), -(m_direction.Dot(m_position))));

	return m_viewMatrix;
}

void Camera::Update(float deltaTime)
{
	//Placeholder controls
}
