#include "Quad.h"
#include "Novice.h"

namespace {
	
	const std::array<Vector2, Quad::kVertexCount>& originalVertices() {
		static const std::array<Vector2, Quad::kVertexCount> original = { { {-0.5f,  0.5f},{0.5f,  0.5f},{-0.5f, -0.5f},{ 0.5f, -0.5f} } };
		return original;
	}
	std::array<Vector2, Quad::kVertexCount> getVertices(const Matrix33& mat) {
		std::array<Vector2, Quad::kVertexCount> result;
		auto r = result.begin();
		for (const auto& it : originalVertices()) {
			*r = it * mat;
			r++;
		}
		return result;
	}
	const std::array<Vector2, Quad::kVertexCount>& originalVertices100() {
		static const std::array<Vector2, Quad::kVertexCount> original = { { {-50.0f,  50.0f},{50.0f,  50.0f},{-50.0f, -50.0f},{ 50.0f, -50.0f} } };
		return original;
	}
	std::array<Vector2, Quad::kVertexCount> getVertices100(const Matrix33& mat) {
		std::array<Vector2, Quad::kVertexCount> result;
		auto r = result.begin();
		for (const auto& it : originalVertices100()) {
			*r = it * mat;
			r++;
		}
		return result;
	}
}




const std::array<Vector2, Quad::kVertexCount>& Quad::vertices()
{
	return originalVertices();
}

std::array<Vector2, Quad::kVertexCount> Quad::vertices(const Matrix33& mat)
{
	return getVertices(mat);
}

void Quad::DrawBoxT(const Matrix33& mat, unsigned int color)
{
	
	std::array<Vector2, kVertexCount> vert;
	vert = getVertices(mat);
	Novice::DrawTriangle(
		(int)vert[0].x, (int)vert[0].y, (int)vert[1].x, (int)vert[1].y,
		(int)vert[2].x, (int)vert[2].y, color, kFillModeSolid);
	Novice::DrawTriangle(
		(int)vert[1].x, (int)vert[1].y, (int)vert[2].x, (int)vert[2].y,
		(int)vert[3].x, (int)vert[3].y, color, kFillModeSolid);
}

void Quad::DrawBoxQ(const Matrix33& mat, unsigned int color)
{
	std::array<Vector2, kVertexCount> vert;
	vert = getVertices(mat);
	Novice::DrawQuad(
		(int)vert[0].x, (int)vert[0].y, (int)vert[1].x, (int)vert[1].y,
		(int)vert[2].x, (int)vert[2].y, (int)vert[3].x, (int)vert[3].y,
		0, 0, 256, 256, 0, color);
}

void Quad::DrawTexture(const Matrix33& mat, int x, int y, int w, int h, int handle, unsigned int color)
{
	std::array<Vector2, kVertexCount> vert;
	vert = getVertices(mat);
	Novice::DrawQuad(
		(int)vert[0].x, (int)vert[0].y, (int)vert[1].x, (int)vert[1].y,
		(int)vert[2].x, (int)vert[2].y,	(int)vert[3].x, (int)vert[3].y,
		x, y, w, h, handle, color);
}

void Quad::DrawBoxQ100(const Matrix33& mat, unsigned int color)
{
	std::array<Vector2, kVertexCount> vert;
	vert = getVertices100(mat);
	Novice::DrawQuad(
		(int)vert[0].x, (int)vert[0].y, (int)vert[1].x, (int)vert[1].y,
		(int)vert[2].x, (int)vert[2].y, (int)vert[3].x, (int)vert[3].y,
		0, 0, 256, 256, 0, color);
}
