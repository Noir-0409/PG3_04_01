#include <Novice.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	float posX = 100.0f;
	float posY = 100.0f;
	float radius = 30.0f;
	float speed = 7.0f;

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
		/// 
		if (keys[DIK_W]) {
			posY = posY + speed;
		}

		if (keys[DIK_S]) {
			posY = posY - speed;
		}

		if (keys[DIK_A]) {
			posX = posX - speed;
		}

		if (keys[DIK_D]) {
			posX = posX + speed;
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
		/// 
		Novice::DrawEllipse((int)scsX, (int)scsY, (int)radius, (int)radius, 0.0f, WHITE, kFillModeSolid);
		
		Novice::DrawLine(0, (int)wcsY, 1280, (int)wcsY, WHITE);

		///
		/// 
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
