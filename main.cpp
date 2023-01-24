#include <Novice.h>
#include "Input.h"
#include "Camera.h"
#include "Quad.h"
#include "Transform.h"
#include "Random.h"

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

	Transform cameratrans;

	Transform center;
	center.position = Vector2(100, 0);
	float rot = 0.0f;
	center.scale = Vector2(1, 1);
	center.parent = &cameratrans;
	
	const int kNum = 100;
	Transform transforms[kNum];
	unsigned int color[kNum] = {};
	int i = 0;
	for (auto& it : transforms) {
		it.position.x = Math::Lerp(Random(), -640.0f, 640.0f);
		it.position.y = Math::Lerp(Random(), -360.0f, 360.0f);
		float s = Math::Lerp(Random(), 0.1f, 1.0f);
		it.scale = Vector2(s, s);
		it.parent = &center;
		float h = Random() * 360.0f;
		color[i] = Color::HsvaToRgba(h, 0xFF, 0xFF, 0x66);
		i++;
	}


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		rot = 0;
		if (input->PushKey(DIK_Q)) {
			rot += Math::ToRadians(1.0f);
		}
		if (input->PushKey(DIK_E)) {
			rot += -Math::ToRadians(1.0f);
		}
		center.position = Rotated(center.position, rot);
		center.rotate += rot;
		
		if (input->PushKey(DIK_W)) {
			center.position.y += 3;
		}
		if (input->PushKey(DIK_S)) {
			center.position.y += -3;
		}
		if (input->PushKey(DIK_D)) {
			center.position.x += 3;
		}
		if (input->PushKey(DIK_A)) {
			center.position.x += -3;
		}
		
		cameratrans.position = camera.position;

		camera.UpdateMatrix();
		cameratrans.UpdateMatrix();
		center.UpdateMatrix();
		for (auto& it : transforms) {
			it.UpdateMatrix();
		}

		Quad::DrawBoxQ100(center.world * camera.vpVpMatrix(),BLACK);
		i = 0;
		for (auto& it : transforms) {
			Quad::DrawBoxQ100(it.world * camera.vpVpMatrix(), color[i]);
			i++;
		}

		Vector2 t = cameratrans.position * camera.vpVpMatrix();
		Novice::DrawEllipse(t.x, t.y, 20, 20, 0.0f, WHITE, kFillModeSolid);

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
