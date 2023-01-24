#pragma once
#include "MyMath.h"
#include <array>

class Quad 
{
public:
	static constexpr int kVertexCount = 4;


public:
	static const std::array<Vector2, kVertexCount>& vertices();
	static std::array<Vector2, kVertexCount> vertices(const Matrix33& mat);

	static Vector2 LeftTop(const Matrix33& mat) { return Vector2(-0.5f, 0.5f) * mat; }
	static Vector2 RightTop(const Matrix33& mat) { return Vector2(0.5f, 0.5f) * mat; }
	static Vector2 LeftBottom(const Matrix33& mat) { return Vector2(-0.5f, -0.5f) * mat; }
	static Vector2 RightBottom(const Matrix33& mat) { return Vector2(0.5f, -0.5f) * mat; }

	static void DrawBoxT(const Matrix33& mat, unsigned int color = 0xFFFFFFFF);
	static void DrawBoxQ(const Matrix33& mat, unsigned int color = 0xFFFFFFFF);
	static void DrawTexture(const Matrix33& mat, int x, int y, int w, int h, int handle, unsigned int color = 0xFFFFFFFF);

	static void DrawBoxQ100(const Matrix33& mat, unsigned int color = 0xFFFFFFFF);

private:
	Quad() {}
	~Quad() {}
};
