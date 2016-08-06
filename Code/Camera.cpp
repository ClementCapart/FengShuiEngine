#include "FengShuiEngine_PCH.h"
#include "Camera.h"


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

void Camera::SetLookAtPosition(Vector3 positionToLookAt)
{
	
}

void Camera::SetPerspective(float fov, float aspectRatio, float nearClipPlane, float farClipPlane)
{
	if (fov <= 0.0f || aspectRatio == 0)
	{
		return;
	}

	m_projectionMatrix.SetIdentity();

	float frustrumDepth = farClipPlane - nearClipPlane;
	float oneOverDepth = 1.0f / frustrumDepth;

	m_projectionMatrix.SetValue(1, 1, 1.0f / std::tan(0.5f * (fov / 180.0f * M_PI)));
	m_projectionMatrix.SetValue(0, 0, m_projectionMatrix.GetValue(1, 1) / aspectRatio);
	m_projectionMatrix.SetValue(2, 2, farClipPlane * oneOverDepth);
	m_projectionMatrix.SetValue(3, 2, (-farClipPlane * nearClipPlane) * oneOverDepth);
	m_projectionMatrix.SetValue(2, 3, 1.0f);
	m_projectionMatrix.SetValue(3, 3, 0.0f);
}
