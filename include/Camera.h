#pragma once
#include "MyMath.h"
#include <vector>

class Camera
{
public:
	Vector2 position = { 640.0f,360.0f };
	Vector2 size = { 1280.0f,720.0f };

	Vector2 viewPortLeftTop = { 0,0 };
	Vector2 viewPortSize = { 1280.0f,720.0f };

private:
	Vector2 m_windowSize = { 1280.0f,720.0f };
	Matrix33 m_cameraWorldMatrix;
	Matrix33 m_viewMatrix;
	Matrix33 m_orthoMatrix;
	Matrix33 m_viewportMatrix;
	Matrix33 m_vpVpMatrix;
	Matrix33 m_vpVpInvMatrix;

public:
	Camera();
	void Initalize(int windowWidth = 1280, int windowHeight = 720);
	void UpdateMatrix();
	void DrawAxis();
	Vector2 Transform(const Vector2& vec) const;
	Vector2 Transform(const Vector2& vec, const Matrix33& world) const;
	std::vector<Vector2> Transform(const std::vector<Vector2>& vec, const Matrix33& world) const;

	const Matrix33& vpVpMatrix() const { return m_vpVpMatrix; }
	const Matrix33& vpVpInvMatrix() const { return m_vpVpMatrix; }
	const Vector2& windowSize() const { return m_windowSize; }


	float ScreenLeft() const;
	float ScreenRight() const;
	float ScreenTop() const;
	float ScreenBottom() const;
};