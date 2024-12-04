#include <Novice.h>

struct Ball {
	int posX;
	int speed;
	int acc;
	int ver;
	int r;
};

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

Ball ball = {
		50,
		15,
		0,
		0,
		50
};

Ball ball2 = {
		50,
		15,
		1,
		0,
		50
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

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

		ball.posX += ball.speed;

		if (ball.posX >= 1230) {

			ball.speed = 0;

		}

		ball2.ver += ball2.acc;

		ball2.posX += ball2.ver;

		if (ball2.posX >= 1230) {

			ball2.acc = 0;

			ball2.ver = 0;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse(ball.posX, 240, ball.r, ball.r, 0.0f, RED, kFillModeSolid);

		Novice::DrawEllipse(ball2.posX, 480, ball.r, ball.r, 0.0f, RED, kFillModeSolid);

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
