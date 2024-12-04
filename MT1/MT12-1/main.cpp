#include <Novice.h>

const char kWindowTitle[] = "MT12-1";

struct Vector2 {
	float x;
	float y;
};

struct Ball {
	Vector2 position;
	Vector2 velosity;
	Vector2 acceleration;
	float radius;
	unsigned int coler;
};

struct Vector2 WCS {
	0,

		500
};
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	struct Ball ball {
		{100, 50},
		{ 30.0f,0.0f },
		{ 0,0 },
			50.0f,
			WHITE
	};

	float e = 0.8f;
	ball.velosity.x = 30.0f;
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


		ball.position.x += ball.velosity.x;


		if (ball.position.x >= 1280 - ball.radius) {
			ball.position.x = 1280 - ball.radius;
			ball.velosity.x = -ball.velosity.x * e;
		}
		if (ball.position.x <= 0 + ball.radius) {
			ball.position.x = 0 + ball.radius;
			ball.velosity.x = -ball.velosity.x * e;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse(static_cast<int>(ball.position.x), static_cast<int>(ball.position.y - WCS.y) * -1,
			static_cast<int>(ball.radius), static_cast<int>(ball.radius), 0.0f, WHITE, kFillModeSolid);

		Novice::DrawLine(0, static_cast<int>(0 - WCS.y) * -1, 1280, static_cast<int>(0 - WCS.y) * -1, WHITE);
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
