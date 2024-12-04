#include <Novice.h>

const char kWindowTitle[] = "夏休みゲーム";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//　変数宣言

	//　自機の情報
	float playerPosX = 250.0f;
	float playerPosY = 410.0f;
	float playerWidth = 50.0f;
	float playerHeight = 50.0f;
	float playerSpeed = 7.0f;

	//　敵機の情報
	float enemyPosX = 1000.0f;
	float enemyPosY = 410.0f;
	float enemyWidth = 50.0f;
	float enemyHeight = 50.0f;

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

		//　ジョジョの移動処理

		if (keys[DIK_A] || keys[DIK_LEFT]) {

			playerPosX = playerPosX - playerSpeed;

		}

		if (keys[DIK_D] || keys[DIK_RIGHT]) {

			playerPosX = playerPosX + playerSpeed;

		}

		if (keys[DIK_W] || keys[DIK_UP]) {

			playerPosY = playerPosY - playerSpeed;

		}

		if (keys[DIK_S] || keys[DIK_DOWN]) {

			playerPosY = playerPosY + playerSpeed;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawBox((int)playerPosX, (int)playerPosY, (int)playerWidth, (int)playerHeight, 0.0f, BLUE, kFillModeSolid);

		Novice::DrawBox((int)enemyPosX, (int)enemyPosY, (int)enemyWidth, (int)enemyHeight, 0.0f, RED, kFillModeSolid);

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
