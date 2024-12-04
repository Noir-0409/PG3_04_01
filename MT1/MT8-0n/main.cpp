#include <Novice.h>
#include <Math.h>
#include <Vector2.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	float posX = 400.0f;
	float posY = 400.0f;
	float speed = 5.0f;
	
	float x = 0.0f;
	float y = 0.0f;
	
	float length = sqrtf(x * x + y * y);

	

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

		Vector2 move = { 0,0 };
		
		if (keys[DIK_W]) {

			move.y += -1;

		}

		if (keys[DIK_S]) {

			move.y += 1;

		}

		if (keys[DIK_A]) {

			move.x+=-1;

		}

		if (keys[DIK_D]) {

			move.x+=1;

		}

		length = sqrtf(move.x * move.x + move.y * move.y);

		if (length != 0.0f) {

			posX += move.x / length*speed;
			posY += move.y / length*speed;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox((int)posX, (int)posY, 100, 100, 0.0f, WHITE, kFillModeSolid);

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
