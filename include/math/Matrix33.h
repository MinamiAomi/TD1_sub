#pragma once
#include "Vector2Math.h"
#include <math.h>
#include <cassert>

class Matrix33 {

public:
	float m[3][3];

public:
	Matrix33(
		float _11 = 1.0f, float _12 = 0.0f, float _13 = 0.0f,
		float _21 = 0.0f, float _22 = 1.0f, float _23 = 0.0f,
		float _31 = 0.0f, float _32 = 0.0f, float _33 = 1.0f) {
		m[0][0] = _11, m[0][1] = _12, m[0][2] = _13;
		m[1][0] = _21, m[1][1] = _22, m[1][2] = _23;
		m[2][0] = _31, m[2][1] = _32, m[2][2] = _33;
	}

	Vector2 GetTranslation() const {
		return { m[2][0],m[2][1] };
	}

	friend inline Matrix33 operator*(const Matrix33& mat1, const Matrix33& mat2) {
		return {
			mat1.m[0][0] * mat2.m[0][0] + mat1.m[0][1] * mat2.m[1][0] + mat1.m[0][2] * mat2.m[2][0],
			mat1.m[0][0] * mat2.m[0][1] + mat1.m[0][1] * mat2.m[1][1] + mat1.m[0][2] * mat2.m[2][1],
			mat1.m[0][0] * mat2.m[0][2] + mat1.m[0][1] * mat2.m[1][2] + mat1.m[0][2] * mat2.m[2][2],

			mat1.m[1][0] * mat2.m[0][0] + mat1.m[1][1] * mat2.m[1][0] + mat1.m[1][2] * mat2.m[2][0],
			mat1.m[1][0] * mat2.m[0][1] + mat1.m[1][1] * mat2.m[1][1] + mat1.m[1][2] * mat2.m[2][1],
			mat1.m[1][0] * mat2.m[0][2] + mat1.m[1][1] * mat2.m[1][2] + mat1.m[1][2] * mat2.m[2][2],

			mat1.m[2][0] * mat2.m[0][0] + mat1.m[2][1] * mat2.m[1][0] + mat1.m[2][2] * mat2.m[2][0],
			mat1.m[2][0] * mat2.m[0][1] + mat1.m[2][1] * mat2.m[1][1] + mat1.m[2][2] * mat2.m[2][1],
			mat1.m[2][0] * mat2.m[0][2] + mat1.m[2][1] * mat2.m[1][2] + mat1.m[2][2] * mat2.m[2][2]
		};
	}

	friend inline Vector2 operator*(const Vector2& vec, const Matrix33& mat) {
		return {
			vec.x * mat.m[0][0] + vec.y * mat.m[1][0] + 1.0f * mat.m[2][0],
			vec.x * mat.m[0][1] + vec.y * mat.m[1][1] + 1.0f * mat.m[2][1]
		};
	}

	inline Matrix33& operator*=(const Matrix33& mat) {
		*this = *this * mat;
		return *this;
	}
	friend inline Matrix33 operator*(float s, const Matrix33& mat) {
		return {
			s * mat.m[0][0], s * mat.m[0][1], s * mat.m[0][2],
			s * mat.m[1][0], s * mat.m[1][1], s * mat.m[1][2],
			s * mat.m[2][0], s * mat.m[2][1], s * mat.m[2][2] };
	}
	friend inline Matrix33 operator*(const Matrix33& mat, float s) {
		return {
			mat.m[0][0] * s, mat.m[0][1] * s, mat.m[0][2] * s,
			mat.m[1][0] * s, mat.m[1][1] * s, mat.m[1][2] * s,
			mat.m[2][0] * s, mat.m[2][1] * s, mat.m[2][2] * s };
	}
	// 単位行列
	static inline Matrix33 Identity() {
		return {
			1,		0,		0,
			0,		1,		0,
			0,		0,		1
		};
	}
	// 拡大縮小行列
	static inline Matrix33 MakeScaling(float scaleX, float scaleY) {
		return {
			scaleX, 0,		0,
			0,		scaleY,	0,
			0,		0,		1
		};
	}
	// 拡大縮小行列
	static inline Matrix33 MakeScaling(float scale) {
		return MakeScaling(scale, scale);
	}
	// 拡大縮小行列
	static inline Matrix33 MakeScaling(const Vector2& scale) {
		return MakeScaling(scale.x, scale.y);
	}
	// 回転行列
	static inline Matrix33 MakeRotation(float theta) {
		float s = sinf(theta);
		float c = cosf(theta);
		return {
			c,		s,		0,
			-s,		c,		0,
			0,		0,		1
		};
	}
	// 平行移動行列
	static inline Matrix33 MakeTranslation(float vecX, float vecY) {
		return {
			1,		0,		0,
			0,		1,		0,
			vecX,	vecY,	1
		};
	}
	// 平行移動行列
	static inline Matrix33 MakeTranslation(const Vector2& vector) {
		return MakeTranslation(vector.x, vector.y);
	}
	// アフィン変換行列
	static inline Matrix33 MakeAffine(float scaleX, float scaleY, float theta, float vecX, float vecY) {
		float s = sinf(theta);
		float c = cosf(theta);
		return {
			scaleX * c,		scaleX * s,		0,
			scaleY * -s,	scaleY * c,		0,
			vecX,			vecY,			1
		};
	}
	// アフィン変換行列
	static inline Matrix33 MakeAffine(float scale, float theta, const Vector2& vec) {
		return MakeAffine(scale, scale, theta, vec.x, vec.y);
	}
	// アフィン変換行列
	static inline Matrix33 MakeAffine(const Vector2& scale, float theta, const Vector2& vec) {
		return MakeAffine(scale.x, scale.y, theta, vec.x, vec.y);
	}

	inline float Determinant() const {
		return m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1]
			- m[0][2] * m[1][1] * m[2][0] - m[0][1] * m[1][0] * m[2][2] - m[0][0] * m[1][2] * m[2][1];
	}

	inline Matrix33 Adjugate() const {
		return {
			  m[1][1] * m[2][2] - m[1][2] * m[2][1],
			-(m[0][1] * m[2][2] - m[0][2] * m[2][1]),
			  m[0][1] * m[1][2] - m[0][2] * m[1][1],

			-(m[1][0] * m[2][2] - m[1][2] * m[2][0]),
			  m[0][0] * m[2][2] - m[0][2] * m[2][0],
			-(m[0][0] * m[1][2] - m[0][2] * m[1][0]),

			  m[1][0] * m[2][1] - m[1][1] * m[2][0],
			-(m[0][0] * m[2][1] - m[0][1] * m[2][0]),
			  m[0][0] * m[1][1] - m[0][1] * m[1][0] };
	}

	inline Matrix33 Inverse() const {
		float det = Determinant();
		assert(det != 0.0f); // 0の場合逆行列がない
		return 1.0f / det * Adjugate();
	}

	static inline Matrix33 MakeInverse(const Matrix33& mat) {
		return mat.Inverse();
	}

	inline Matrix33 Transpose() const {
		return {
			m[0][0],m[1][0],m[2][0],
			m[0][1],m[1][1],m[2][1],
			m[0][2],m[1][2],m[2][2] };
	}

	static inline Matrix33 MakeOrthographic(float left, float top, float right, float bottom) {
		return {
			2 / (right - left) ,						0,									0,
			0,										2 / (top - bottom),					0,
			(left + right ) / (left - right),		(top + bottom) / (bottom - top),	1	};

	}

	static inline Matrix33 MakeViewport(float left, float top, float width, float height) {
		float halfW = width / 2.0f;
		float halfh = height / 2.0f;
		return {
			halfW,			0,				0,
			0,				-halfh,			0,
			left + halfW,	top + halfh,	1 };
	}


};