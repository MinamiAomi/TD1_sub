#pragma once
#include "Vector2.h"
#include <math.h>

#pragma region ���Z�q

inline Vector2 operator+(const Vector2& v1, const Vector2& v2) {
	return { v1.x + v2.x, v1.y + v2.y };
}
inline Vector2 operator-(const Vector2& v1, const Vector2& v2) {
	return { v1.x - v2.x, v1.y - v2.y };
}
inline Vector2 operator*(const Vector2& v1, float s) {
	return { v1.x * s, v1.y * s };
}
inline Vector2 operator/(const Vector2& v1, float s) {
	return { v1.x / s, v1.y / s };
}
inline Vector2 operator*(float s, const Vector2& v1) {
	return { s * v1.x, s * v1.y };
}
inline Vector2 operator*(const Vector2& v1, const Vector2& v2) {
	return { v1.x * v2.x, v1.y * v2.y };
}

#pragma endregion


// Vector2�̌v�Z

	// ����
inline float Dot(const Vector2& v1, const Vector2& v2) {
	return v1.x * v2.x + v1.y * v2.y;
}
	// �O��
inline float Cross(const Vector2& v1, const Vector2& v2) {
	return v1.x * v2.y - v1.y * v2.x;
}
	// �����̓��
inline float LengthSquare(const Vector2& v) {
	return Dot(v, v);
}
	// ����
inline float Length(const Vector2& v) {
	return sqrtf(LengthSquare(v));
}
	// ���x�N�g���Ƃ̋���
inline float Distance(const Vector2& v1, const Vector2& v2) {
	return Length(v2 - v1);
}
	// �Ȃ��p
inline float Angle(const Vector2& v) {
	return atan2f(v.y, v.x);
}
	// ���K��
inline Vector2 Normalized(const Vector2& v) {
	float len = Length(v);
	return len != 0 ? v / len : v; // ������0�o�Ȃ����m�F
}
	// �@��
inline Vector2 Normal(const Vector2& v) {
	return { -v.y, v.x };
}
	// ��]
inline Vector2 Rotated(const Vector2& v, float theta) {
	float s = sinf(theta);
	float c = cosf(theta);
	return { v.x * c + v.y * -s, v.x * s + v.y * c };
}
// ���`���
inline Vector2 Lerp(float t, const Vector2& start, const Vector2& end) {
	return start + t * (end - start);
}

	// ���˃x�N�g��
	// �������͕ǂ̖@���𐳋K�������x�N�g��
inline Vector2 Reflected(const Vector2& v, const Vector2& normal) {
	return Dot(normal, -v) * 2 * normal + v;
}
	// �ǂ���x�N�g��
	// �������͕ǂ̖@���𐳋K�������x�N�g��
inline Vector2 AlongWall(const Vector2& v, const Vector2& normal) {
	return Dot(normal, -v) * normal + v;
}
	// �[���ɂ���
inline void SetZero(Vector2& v) {
	v.x = 0;
	v.y = 0;
}
	// �[���ł��邩
inline bool IsZero(const Vector2& v) {
	return { v.x == 0.0f && v.y == 0.0f };
}



static const Vector2 Vec2Zero = { 0.0f,0.0f };
static const Vector2 Vec2UnitX = { 1.0f,0.0f };
static const Vector2 Vec2UnitY = { 0.0f,1.0f };
