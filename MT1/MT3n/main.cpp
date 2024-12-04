#include <Novice.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	float leftA = 400.0f;
	float rightA = 500.0f;
	float topA = 400.0f;
	float bottomA = 500.0f;

	float leftB = 100.0f;
	float rightB = 150.0f;
	float topB = 100.0f;
	float bottomB = 150.0f;

	float speed = 7.0f;

	int isHitX = false;
	int isHitY = false;
	int isHit = false;

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

		if (keys[DIK_A]) {
			leftB = leftB - speed;
			rightB = rightB - speed;
		}

		if (keys[DIK_D]) {
			leftB = leftB + speed;
			rightB = rightB + speed;
		}

		if (keys[DIK_W]) {
			topB = topB - speed;
			bottomB = bottomB - speed;
		}

		if (keys[DIK_S]) {
			topB = topB + speed;
			bottomB = bottomB + speed;
		}

		if (leftB < rightA && leftA < rightB) {

			isHitX = true;

		} else {

			isHitX = false;

		}

			if (topA < bottomB && topB < bottomA) {

				isHitY = true;
			
			} else {

				isHitY = false;

			}

			if (isHitX && isHitY) {

				isHit = true;

			} else {

				isHit = false;

			}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		Novice::DrawBox((int)leftA, (int)topA, 100, 100, 0.0f, WHITE, kFillModeSolid);

		if (isHit == false) {
			Novice::DrawBox((int)leftB, (int)topB, 50, 50, 0.0f, RED, kFillModeSolid);
		} else {
			Novice::DrawBox((int)leftB, (int)topB, 50, 50, 0.0f, BLUE, kFillModeSolid);
		}

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
