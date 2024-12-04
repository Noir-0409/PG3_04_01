#include <Novice.h>
#define _USE_MATH_DEFINES
#include <Math.h>
#include <Vector2.h>


const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	struct Vector2
	{
		float x;
		float y;

	};

	Vector2 A{
		A.x = 600.0f,
		A.y = 400.0f
	};

	Vector2 B{};

	Vector2 V{
		V.x = 300.0f,
		V.y = 200.0f
	};

	Vector2 newV{};

	float k = 1.0f;

	float theta = (1.0f / 4.0f) * (float)M_PI;

	int newVChange = true;

	Vector2 rotatedNewV{
		rotatedNewV.x = 0.0f, 
		rotatedNewV.y = 0.0f
	};

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

		
		newV.x = V.x * k;
		newV.y = V.y * k;

		if (newVChange) {
			k += 0.01f;
			if (newV.x >= V.x * 2) {
				newVChange = false;
			}
		} else {
			k -= 0.01f;
			if (newV.x <= V.x * 0.5f) {
				newVChange = true;
			}
		}

		theta += 1.0f / 64.0f * float(M_PI);
			rotatedNewV.x = newV.x * cosf(theta) - newV.y * sinf(theta);
			rotatedNewV.y = newV.x * sinf(theta) + newV.y * cosf(theta);

	

			B.x = A.x + rotatedNewV.x;
			B.y = A.y + rotatedNewV.y;
				
		///
		/// ↑更新処理ここまで
		///


		///
		/// ↓描画処理ここから
		///

			Novice::DrawLine((int)A.x, (int)A.y, (int)B.x, (int)B.y, WHITE);

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
