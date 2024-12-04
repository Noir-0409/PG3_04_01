#include <Novice.h>
#define _USE_MATH_DEFINES
#include <Math.h>
const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	float whiteX = 300.0f;
	float whiteY = 300.0;
	float whiteRadius = 50.0f;

	float redX = 800.0f;
	float redY = 500.0f;
	float redRadius = 50.0f;

	float t = 0.1f;


	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

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

		Novice::DrawEllipse((int)whiteX, (int)whiteY, (int)whiteRadius, (int)whiteRadius, 0.0f, WHITE, kFillModeSolid);

		Novice::DrawEllipse((int)redX, (int)redY, (int)redRadius, (int)redRadius, 0.0f, RED , kFillModeSolid);


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
