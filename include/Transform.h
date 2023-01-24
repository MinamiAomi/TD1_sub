#pragma once
#include "MyMath.h"

struct Transform
{
	// ���W
	Vector2 position = {};
	// ��]
	float rotate = {};
	// �X�P�[��
	Vector2 scale = { 1.0f,1.0f };
	// ���[���h�s��
	Matrix33 world;
	// �e
	Transform* parent = nullptr;


	inline void UpdateMatrix() {
		world = Matrix33::MakeScaling(scale);
		world *= Matrix33::MakeRotation(rotate);
		world *= Matrix33::MakeTranslation(position);
		if (parent != nullptr) {
			world *= parent->world;
		}
	}
};
