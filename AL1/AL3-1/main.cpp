#include <Novice.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	int posX = 500;
	int posY = 500;
	int speed = 10;
	int radius = 10;
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

		if (keys[DIK_UP]) {
			posY = posY -speed;
		}

		if (keys[DIK_DOWN]) {
			posY = posY + speed;
		}

		if (keys[DIK_LEFT]) {
			posX = posX - speed;
		}

		if (keys[DIK_RIGHT]) {
			posX = posX + speed;
		}

		if (posY >= 700) {
			posY = posY - radius;
		}

		if (posY <= 20) {
			posY = posY + radius;
		}
		
		if (posX >= 1260) {
			posX = posX - radius;
		}

		if (posX <= 20) {
			posX = posX + radius;
		}
		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse(posX, posY, 30, 30, 0.0f, 0xFFFFFFFF, kFillModeSolid);
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
