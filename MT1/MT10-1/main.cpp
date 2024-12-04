#include <Novice.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	float posX = 600.0f;
	float posY = 0.0f;
	float radius = 100.0f;
	float speed = 10.0f;

	float wcsY = 500.0f;
	float scsX = 0.0f;
	float scsY = 0.0f;

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
	
		if (keys[DIK_SPACE]) {

			posX = posX + speed;

			if (posX >= 1180) {
				speed *= -1;
			}

			else if (posX <= 100) {
				speed *= -1;
			}
		}

		scsY = posY;

		scsX = posX;

		scsY += -wcsY;

		scsY *= -1;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse((int)scsX, (int)scsY, (int)radius, (int)radius, 0.0f, WHITE, kFillModeSolid);
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
