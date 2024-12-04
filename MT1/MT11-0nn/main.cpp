#include <Novice.h>



const char kWindowTitle[] = "MT11-0";

struct Vector2 {
	float x;
	float y;
};

struct Boll {
	Vector2 position;
	Vector2 velosity;
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


	struct Boll turtle {
		{300, 100},
		{ 10,4 },
			50,
			WHITE
	};




	bool isMovingTurtle = false;
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

		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
			isMovingTurtle = true;
		}
		if (isMovingTurtle) {
			turtle.position.x += turtle.velosity.x;
			turtle.position.y += turtle.velosity.y;
		}


		///
		/// ↑更新処理ここまで
		///
		Novice::DrawEllipse(static_cast<int>(turtle.position.x), static_cast<int>(turtle.position.y - WCS.y) * -1,
			static_cast<int>(turtle.radius), static_cast<int>(turtle.radius), 0.0f, static_cast<int>(turtle.coler), kFillModeSolid);
		///
		/// ↓描画処理ここから
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

