#include <Novice.h>

const char kWindowTitle[] = "MT9-1";
struct Vector2 {
	float x;
	float y;
};

struct Cicle {
	Vector2 center;
	float radius;
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	struct Vector2 start {
		300,
			300
	};
	struct Vector2 end {
		800,
			500
	};

	struct Cicle A {
		(300.0f, 300.0f),
			(800.0f, 500.0f),
			50.0f
	};

	struct Cicle B {
		(800.0f, 500.0f),
			(800.0f, 500.0f),
			50.0f
	};

	bool isPush = false;

	float t = 0.0f;

	A.center.x = 300.0f;
	A.center.y = 300.0f;

	B.center.x = 800.0f;
	B.center.y = 500.0f;

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
			isPush = true;
		}

		if (isPush) {
			t += 0.02f;

			A.center.x = (1.0f - t) * start.x + t * end.x;
			A.center.y = (1.0f - t) * start.y + t * end.y;
			if (t > 1.0) {
				isPush = false;
				A.center.x = 800.0f;
				A.center.y = 500.0f;
			}

		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse(static_cast<int>(A.center.x), static_cast<int>(A.center.y)
			, static_cast<int>(A.radius), static_cast<int>(A.radius)
			, 0.0f, WHITE, kFillModeSolid);
		Novice::DrawEllipse(static_cast<int>(B.center.x), static_cast<int>(B.center.y), static_cast<int>(B.radius), static_cast<int>(B.radius)
			, 0.0f, WHITE, kFillModeSolid);



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

