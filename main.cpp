#include <Novice.h>
#include "Input.h"
#include "Camera.h"
#include "Quad.h"
#include "Transform.h"
#include "Random.h"

#include <vector>

const char kWindowTitle[] = "学籍番号";
const int kWindowWidth = 1280;
const int kWindowHeight = 720;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	SrandFromTime();
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, kWindowWidth, kWindowHeight);
	auto input = Input::GetInstance();

	Camera camera;
	camera.Initalize();
	camera.position = Vec2Zero;



	Transform center;
	center.position = Vector2(0, 0);
	float rot = 0.0f;
	center.scale = Vector2(0.5, 0.5);
	
	const int kNum = 100;
	Transform transforms[kNum];
	unsigned int color[kNum] = {};
	int i = 0;
	for (auto& it : transforms) {
		it.position.x = Math::Lerp(Random(), -640.0f * 2, 640.0f * 2);
		it.position.y = Math::Lerp(Random(), -360.0f * 2, 360.0f * 2);
		float s = Math::Lerp(Random(), 0.1f, 1.0f);
		it.scale = Vector2(s, s);
		it.parent = &center;
		float h = Random() * 360.0f;
		color[i] = Color::HsvaToRgba(h, 0xFF, 0xFF, 0x66);
		i++;
	}

	Vector2 ball = { 0,300 };

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		rot = 0;
		if (input->PushKey(DIK_Q)) {
			rot += Math::ToRadians(2.0f);
		}
		if (input->PushKey(DIK_E)) {
			rot += -Math::ToRadians(2.0f);
		}
	
		center.position = Rotated(center.position, rot);
		center.rotate += rot;
		
		if (input->PushKey(DIK_W)) {
			center.position.y += 5;
		}
		if (input->PushKey(DIK_S)) {
			center.position.y += -5;
		}
		if (input->PushKey(DIK_D)) {
			center.position.x += 5;
		}
		if (input->PushKey(DIK_A)) {
			center.position.x += -5;
		}
	
		ball.y -= 3.0f;

		camera.UpdateMatrix();
		center.UpdateMatrix();
		for (auto& it : transforms) {
			it.UpdateMatrix();
		}

		//i = 0;
		//for (auto& it : transforms) {
		//	Quad::DrawBoxQ100(it.world * camera.vpVpMatrix(), color[i]);
		//	i++;
		//}
		//i = 0;
		//
		//Quad::DrawBoxQ100(center.world * camera.vpVpMatrix(),BLACK);

		camera.DrawAxis();
		{
			Vector2 t = camera.position * camera.vpVpMatrix();
			Vector2 cen = (center.world * camera.vpVpMatrix()).GetTranslation();

			std::vector<Vector2> src;
			i = 0;
			for (auto& it : transforms) {
				src.emplace_back();
				src[i] = (it.world * camera.vpVpMatrix()).GetTranslation();
				Novice::DrawEllipse(src[i].x, src[i].y, 5, 5, 0.0f, color[i], kFillModeSolid);
				Novice::DrawLine(cen.x, cen.y, src[i].x, src[i].y, WHITE);
				i++;
			}
			i = 0;

			Novice::DrawLine(cen.x, cen.y, t.x, t.y, BLACK);

			Novice::DrawEllipse(cen.x, cen.y, 10, 10, 0.0f, BLACK, kFillModeSolid);
			Novice::DrawEllipse(t.x, t.y, 20, 20, 0.0f, WHITE, kFillModeSolid);
		
			Vector2 s = ball * camera.vpVpMatrix();
			Novice::DrawEllipse(s.x, s.y, 50, 50, 0.0f, WHITE, kFillModeSolid);

			Vector2 s1 = Vector2{ -640.0f * 2,-360.0f * 2 } * center.world * camera.vpVpMatrix();
			Vector2 s2 = Vector2{ -640.0f * 2,360.0f * 2 } * center.world * camera.vpVpMatrix();
			Vector2 s3 = Vector2{ 640.0f * 2,-360.0f * 2 } * center.world * camera.vpVpMatrix();
			Vector2 s4 = Vector2{ 640.0f * 2,360.0f * 2 } * center.world * camera.vpVpMatrix();
			Novice::DrawLine(s1.x, s1.y, s2.x, s2.y, WHITE);
			Novice::DrawLine(s4.x, s4.y, s2.x, s2.y, WHITE);
			Novice::DrawLine(s3.x, s3.y, s4.x, s4.y, WHITE);
			Novice::DrawLine(s1.x, s1.y, s3.x, s3.y, WHITE);
		}
		
		

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (input->TriggerKey(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
