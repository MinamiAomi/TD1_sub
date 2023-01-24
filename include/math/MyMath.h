#pragma once
#include "Vector2Math.h"
#include "Matrix33.h"
#include <math.h>
#include <array>

namespace Math
{

	constexpr float Pi = 3.14159265359f;
	constexpr float TwoPi = 2.0f * Pi;


	/// <summary>
	/// �ʓx�@�ϊ�
	/// </summary>
	/// <param name="degrees">�x���@</param>
	/// <returns>�ʓx�@</returns>
	constexpr inline float ToRadians(float degrees) {
		return degrees * Pi / 180.0f;
	}
	/// <summary>
	/// �x���@�ϊ�
	/// </summary>
	/// <param name="radians">�ʓx�@</param>
	/// <returns>�x���@</returns>
	constexpr inline float ToDegrees(float radians) {
		return radians * 180.0f / Pi;
	}
	/// <summary>
	/// �����𔻒f
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="v">�l</param>
	/// <returns> 0��0 </returns>
	template <typename TYPE>
	int GetSign(TYPE v) {
		return (v > 0) - (v < 0);
	}
	/// <summary>
	/// �傫���ق������߂�
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="v1">�l�P</param>
	/// <param name="v2">�l�Q</param>
	/// <returns>�l�P�@or�@�l�Q</returns>
	template <typename TYPE>
	TYPE Max(const TYPE& v1, const TYPE& v2) {
		return v1 < v2 ? v2 : v1;
	}
	/// <summary>
	/// �������ق������߂�
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="v1">�l�P</param>
	/// <param name="v2">�l�Q</param>
	/// <returns>�l�P�@or�@�l�Q</returns>
	template <typename TYPE>
	TYPE Min(const TYPE& v1, const TYPE& v2) {
		return v1 < v2 ? v1 : v2;
	}
	/// <summary>
	/// �l�����߂�
	/// </summary>
	/// <typeparam name="TYPE">�^</typeparam>
	/// <param name="value">�l</param>
	/// <param name="lower">����</param>
	/// <param name="upper">���</param>
	/// <returns></returns>
	template <typename TYPE>
	TYPE Clamp(const TYPE& value, const TYPE& lower, const TYPE& upper) {
		return Min(upper, Max(lower, value));
	}
	/// <summary>
	/// �l�����[�v������
	/// </summary>
	/// <param name="value">�l</param>
	/// <param name="range">�͈�</param>
	/// <param name="min">�ŏ�</param>
	/// <returns></returns>
	inline float Loop(float value, float range, float min = 0.0f) {
		if (min < value && value < min + range) return value;
		float x = fmodf(value - min, range);
		if (x < 0) {
			x += range;
		}
		return x + min;
	}
	/// <summary>
	/// ��Βl
	/// </summary>
	/// <param name="value">�l</param>
	/// <returns></returns>
	inline float Abs(float value) {
		return fabsf(value);
	}
	/// <summary>
	///	�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Sin(float angle) {
		return sinf(angle);
	}
	/// <summary>
	/// �R�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Cos(float angle) {
		return cosf(angle);
	}
	/// <summary>
	/// �^���W�F���g
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Tan(float angle) {
		return tanf(angle);
	}
	/// <summary>
	/// �A�[�N�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Asin(float angle) {
		return asinf(angle);
	}
	/// <summary>
	/// �A�[�N�R�T�C��
	/// </summary>
	/// <param name="angle">���W�A��</param>
	/// <returns></returns>
	inline float Acos(float angle) {
		return acosf(angle);
	}
	/// <summary>
	/// �A�[�N�^���W�F���g
	/// </summary>
	/// <param name="y">y����</param>
	/// <param name="x">x����</param>
	/// <returns>���W�A��</returns>
	inline float Atan2(float y, float x) {
		return atan2f(y, x);
	}
	/// <summary>
	/// ���`���
	/// </summary>
	/// <param name="t">�ω���</param>
	/// <param name="start">�X�^�[�g</param>
	/// <param name="end">�G���h</param>
	/// <returns></returns>
	inline float Lerp(float t, float start, float end) {
		return start + t * (end - start);
	}
	/// <summary>
	/// ���ݔ͈͂���ʂ͈̔͂ɕϊ�
	/// </summary>
	/// <param name="value">�l</param>
	/// <param name="start1">���ݔ͈͂̍ŏ�</param>
	/// <param name="end1">���ݔ͈͂̍ő�</param>
	/// <param name="start2">�ϊ��͈͂̍ŏ�</param>
	/// <param name="end2">�ϊ��͈͂̍ő�</param>
	/// <returns></returns>
	inline float Map(float value, float s1, float e1, float s2, float e2) {
		return (value - s1) / (e1 - s1) * (e2 - s2) + s2;
	}
	//inline float Map(float value, float start1, float end1, float start2, float end2) {
	//	return start2 + (end1 - start2) * ((value - start1) / (end2 - start1));
	//}

	inline float InvLerp(float value, float start, float end) {
		return (value - start) / (end - start);
	}

	/// <summary>
	/// ������
	/// </summary>
	/// <param name="value">�l</param>
	/// <returns></returns>
	inline float Sqrt(float value) {
		return sqrtf(value);
	}
	/// <summary>
	/// float��]���Z
	/// </summary>
	/// <param name="number">�����鐔</param>
	/// <param name="denom">���鐔</param>
	/// <returns>�]��</returns>
	inline float Fmod(float number, float denom) {
		return fmodf(number, denom);
	}
	/// <summary>
	/// �p��
	/// </summary>
	/// <param name="base">��</param>
	/// <param name="exponent">�w��</param>
	/// <returns></returns>
	inline float Pow(float base, float exponent) {
		return powf(base, exponent);
	}

}

namespace Color {

	static const unsigned int kByteMax = 0xFF;

	inline unsigned int Create(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
		return r << 24 | g << 16 | b << 8 | a;
	}

	unsigned int HsvaToRgba(float h, float s, float v, unsigned int a);

	unsigned int Lerp(float t, unsigned int start, unsigned int end);

	inline std::array<unsigned char, 4> Detach(unsigned int rgba) {
		std::array<unsigned char, 4> result = {
			static_cast<unsigned char>(rgba >> 24),
			static_cast<unsigned char>(rgba >> 16),
			static_cast<unsigned char>(rgba >> 8),
			static_cast<unsigned char>(rgba) };
		return result;
	}


	inline unsigned int Connect(const std::array<unsigned char, 4>& colors) {
		return Create(colors[0], colors[1], colors[2], colors[3]);
	};
}