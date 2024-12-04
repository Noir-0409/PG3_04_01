#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>
const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	float aposX = 300.0f;
	float aposY = 50.0f;

	float bposX = 500.0f;
	float bposY = 100.0f;

	float atheta = 1.0f / 8.0f * float(M_PI);
	float btheta = 1.0f / 4.0f * float(M_PI);

	float newaposX = aposX * cosf(atheta) - aposY * sinf(atheta);
	float newaposY = aposY * cosf(atheta) + aposX * sinf(atheta);

	float newbposX = bposX * cosf(btheta) - bposY * sinf(btheta);
	float newbposY = bposY * cosf(btheta) + bposX * sinf(btheta);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawBox((int)aposX, (int)aposY, 100, 100, 0.0f, 0xFFFFFFFF, kFillModeSolid);
		Novice::DrawBox((int)bposX, (int)bposY, 100, 100, 0.0f, 0xFFFFFFFF, kFillModeSolid);
		Novice::DrawBox((int)newaposX, (int)newaposY, 100, 100, 0.0f, RED, kFillModeSolid);
		Novice::DrawBox((int)newbposX, (int)newbposY, 100, 100, 0.0f, BLUE, kFillModeSolid);
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
