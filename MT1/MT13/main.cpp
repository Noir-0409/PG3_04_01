#include <Novice.h>
#include <Math.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	float posX1 = 800.0f;
	float posX2 = 300.0f;
	float posY = 100.0f;
	float radius = 30.0f;
	float speed = 5.0f;

	float wcsY = 500.0f;
	float scsX1 = 0.0f;
	float scsX2 = 0.0f;
	float scsY = 0.0f;

	float mx = 0.0f;
	float tx = posX1 < posX2;

	float my = 0.0f;
	float ty = 0.0f;

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

		if (keys[DIK_A] == false) {

			posX2 = posX2 + speed;

			mx = 1;

		}

		if (keys[DIK_D] == false) {

			posX2 = posX2 - speed;

			mx = -1;

		}

		if (posX2 - posX1 < 0) {

			tx = -1;

		}


		if (posX2 - posX1 > 0) {

			tx = 1;

		}

		float dot = mx * tx + my * ty;
		
		if (dot < 0.0f) {

		}

		scsX1 = posX1;

		scsX2 = posX2;

		scsY = posY;

		scsY += -wcsY;

		scsY *= -1;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		
		if (dot >= 0) {
			Novice::DrawEllipse((int)scsX1, (int)scsY, (int)radius, (int)radius, 0.0f, WHITE, kFillModeSolid);
		} else {
			Novice::DrawEllipse((int)scsX1, (int)scsY, (int)radius, (int)radius, 0.0f, BLUE, kFillModeSolid);
		}

		Novice::DrawEllipse((int)scsX2, (int)scsY, (int)radius, (int)radius, 0.0f, WHITE, kFillModeSolid);

		if (scsX1 - scsX2 >= 0){
			Novice::DrawLine((int)scsX1, (int)scsY, (int)scsX1 + 200*-1, (int)scsY, WHITE);
		} else {
			Novice::DrawLine((int)scsX1, (int)scsY, (int)scsX1 + 200, (int)scsY, WHITE);
		}

		Novice::DrawLine((int)scsX2, (int)scsY, (int)scsX2 + 200*(int)mx, (int)scsY, WHITE);

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
