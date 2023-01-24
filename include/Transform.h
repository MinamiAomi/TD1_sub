#pragma once
#include "MyMath.h"

struct Transform
{
	// 座標
	Vector2 position = {};
	// 回転
	float rotate = {};
	// スケール
	Vector2 scale = { 1.0f,1.0f };
	// ワールド行列
	Matrix33 world;
	// 親
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
