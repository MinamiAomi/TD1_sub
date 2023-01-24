#include "Camera.h"
#include "Novice.h"

Camera::Camera()
{
	UpdateMatrix();
}

void Camera::Initalize(int windowWidth, int windowHeight)
{
	m_windowSize = Vector2(static_cast<float>(windowWidth), static_cast<float>(windowHeight));
	UpdateMatrix();
}


void Camera::UpdateMatrix()
{
	m_cameraWorldMatrix = Matrix33::MakeTranslation(position);
	m_viewMatrix = m_cameraWorldMatrix.Inverse();
	Vector2 halfSize = size / 2.0f;
	m_orthoMatrix = Matrix33::MakeOrthographic(-halfSize.x, halfSize.y, halfSize.x, -halfSize.y);
	m_viewportMatrix = Matrix33::MakeViewport(viewPortLeftTop.x, viewPortLeftTop.y, viewPortSize.x, viewPortSize.y);
	m_vpVpMatrix = m_viewMatrix * m_orthoMatrix * m_viewportMatrix;
	m_vpVpInvMatrix = m_vpVpMatrix.Inverse();
}

void Camera::DrawAxis()
{
	Vector2 scrWorldOrgin = m_vpVpMatrix.GetTranslation();
	Novice::DrawLine(0, static_cast<int>(scrWorldOrgin.y), static_cast<int>(m_windowSize.x), static_cast<int>(scrWorldOrgin.y), RED);
	Novice::DrawLine(static_cast<int>(scrWorldOrgin.x), 0, static_cast<int>(scrWorldOrgin.x), static_cast<int>(m_windowSize.y), BLUE);
}

Vector2 Camera::Transform(const Vector2& vec) const
{
	return vec * m_vpVpMatrix;
}

Vector2 Camera::Transform(const Vector2& vec, const Matrix33& world) const
{
	Matrix33 wvpVpMat = world * m_vpVpMatrix;
	return vec * wvpVpMat;
}

std::vector<Vector2> Camera::Transform(const std::vector<Vector2>& vec, const Matrix33& world) const
{
	Matrix33 wvpVpMat = world * m_vpVpMatrix;
	std::vector<Vector2> transVec;
	for (const auto& iter : vec) {
		transVec.emplace_back(iter * world);
	}
	return transVec;
}

float Camera::ScreenLeft() const
{
	return position.x - m_windowSize.x * 0.5f;
}

float Camera::ScreenRight() const
{
	return position.x + m_windowSize.x * 0.5f;
}

float Camera::ScreenTop() const
{
	return position.y + m_windowSize.y * 0.5f;
}

float Camera::ScreenBottom() const
{
	return position.y - m_windowSize.y * 0.5f;
}
