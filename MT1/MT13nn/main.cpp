#include <Novice.h>
struct  Vector2 {
	float x;
	float y;
};
struct Ball {
	Vector2 pos;
	Vector2 velosity;
	Vector2 accelaration;
	float radius;
	unsigned int color;
};
struct Vector2 WCS {
	0,

		500
};
const char kWindowTitle[] ="MT13";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	struct Ball ball {
		{500, 300},
		{ 30.0f,0.0f },
		{ 0,0 },
			30.0f,
			WHITE
	};

	ball.pos.x = 500;
	ball.pos.y = 300;
	ball.velosity.x = 5;
	ball.velosity.y = 5;
	float lineX[2] = { 100,1000 };
	float lineY[2] = { 100,400 };


	float dot = ball.pos.y * lineX[0] - ball.pos.x * lineY[0];
	float dot2 = ball.pos.y * lineX[1] - ball.pos.x * lineY[1];
	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		dot = ball.pos.y * lineX[0] - ball.pos.x * lineY[0];
		dot2 = ball.pos.y * lineX[1] - ball.pos.x * lineY[1];

		if (keys[DIK_A]) {
			ball.pos.x -= ball.velosity.x;
		}
		if (keys[DIK_D]) {
			ball.pos.x += ball.velosity.x;
		}
		if (keys[DIK_W]) {
			ball.pos.y += ball.velosity.y;
		}
		if (keys[DIK_S]) {
			ball.pos.y -= ball.velosity.y;
		}



		if (dot >= 0) {
			ball.color = BLUE;
		} else {
			ball.color = WHITE;
		}
		if (dot2 >= 0) {
			ball.color = BLUE;
		} else {
			ball.color = WHITE;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawLine(static_cast<int>(lineX[0]), static_cast<int>(lineY[0] - WCS.y) * -1, static_cast<int>(lineX[1]), static_cast<int>(lineY[1] - WCS.y) * -1, WHITE);
		Novice::DrawEllipse(static_cast<int>(ball.pos.x), static_cast<int>(ball.pos.y - WCS.y) * -1,
			static_cast<int>(ball.radius), static_cast<int>(ball.radius)
			, 0.0f, ball.color, kFillModeSolid);
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
main.cpp
3 KB