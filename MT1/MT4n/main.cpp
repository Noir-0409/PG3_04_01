#include <Novice.h>
#define _USE_MATH_DEFINES
#include <Math.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	float posX = 400.0f;
	float posY = 400.0f;
	float widht = 100.0f;
	float height = 100.0f;
	float speed = 7.0f;

	float theta = (1.0f / 2.0f) * float(M_PI);
	float moveX = cosf(theta);
	float moveY = sinf(theta);

	int isMoving = false;

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
			
			isMoving = true;

			theta = 1.0f*float(M_PI);
		
		}

		if (keys[DIK_D]) {

			isMoving = true;

			theta = 0.0f*float(M_PI);

		
		}

		if (keys[DIK_W]) {

			isMoving = true;

			theta = (1.0f / 2.0f)*float(M_PI);
	
		}

		if (keys[DIK_S]) {

			isMoving = true;

			theta = (3.0f / 2.0f)*float(M_PI);
			
		}

		if (keys[DIK_A] && keys[DIK_W]) {

			isMoving = true;

			theta = (3.0f / 4.0f)*float(M_PI);
			
		}

		if (keys[DIK_A] && keys[DIK_S]) {

			isMoving = true;

			theta = (5.0f / 4.0f)*float(M_PI);
		}

		if (keys[DIK_D] && keys[DIK_W]) {

			isMoving = true;

			theta = (1.0f / 4.0f)*float(M_PI);
			
		}

		if (keys[DIK_D] && keys[DIK_S]) {

			isMoving = true;

			theta = (7.0f / 4.0f)*float(M_PI);
			
		}

		if (isMoving) {
			moveX = cosf(theta);

			moveY = sinf(theta) * -1;

			posX += moveX * speed;

			posY += moveY * speed;
		}

		isMoving = false;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox((int)posX, (int)posY, (int)widht, (int)height, 0.0f, WHITE, kFillModeSolid);

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
