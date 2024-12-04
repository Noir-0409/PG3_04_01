#include <Novice.h>
#define _USE_MATH_DEFINES
#include <Math.h>

const char kWindowTitle[] = "MT6";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	float posX = 600.0f;
	float posY = 350.0;

	float theta = (1.0f / 2.0f) * float(M_PI);

	float amplitude = 450.0f;

	posY = sinf(theta) * amplitude;

	theta += float(M_PI) / 30.0f;
	
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
		posY = sinf(theta) * amplitude;

		theta += float(M_PI) / 30.0f;
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse((int)posX, (int)posY+250, 50, 50, 0.0f, 0xFFFFFFFF, kFillModeSolid);
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
