#include <Novice.h>

const char kWindowTitle[] = "AL7";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//　変数宣言

	//　自分の情報
	float posX = 100.0f;
	float posY = 100.0f;
	float speed = 5.0f;

	// 画像の情報
	int GH[4][4] = {

		//　後ろ向きの画像
		{ Novice::LoadTexture("./Resources/Images/back0.png"),
		Novice::LoadTexture("./Resources/Images/back1.png"),
		Novice::LoadTexture("./Resources/Images/back2.png"),
		Novice::LoadTexture("./Resources/Images/back3.png") },

		//　前向きの画像
		{ Novice::LoadTexture("./Resources/Images/front0.png"),
		Novice::LoadTexture("./Resources/Images/front1.png"),
		Novice::LoadTexture("./Resources/Images/front2.png"),
		Novice::LoadTexture("./Resources/Images/front3.png") },

		// 左向きの画像
		{ Novice::LoadTexture("./Resources/Images/left0.png"),
		Novice::LoadTexture("./Resources/Images/left1.png"),
		Novice::LoadTexture("./Resources/Images/left2.png"),
		Novice::LoadTexture("./Resources/Images/left3.png") },

		// 右向きの画像
		{ Novice::LoadTexture("./Resources/Images/right0.png"),
		Novice::LoadTexture("./Resources/Images/right1.png"),
		Novice::LoadTexture("./Resources/Images/right2.png"),
		Novice::LoadTexture("./Resources/Images/right3.png") }
	};

	enum PLAYER_DIRECTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	//　プレイヤーの向きを管理する変数
	int playerDirection = DOWN;

	//　フレームを数える変数
	float frameCounter = 0.0f;

	float animationCount = 0.0f;

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

		frameCounter++;

		if (frameCounter >= 15) {
			
			animationCount++;

			if (animationCount >= 4) {
				
				animationCount = 0;

			}

			frameCounter = 0;
		}

		if (keys[DIK_W]) {

			posY = posY - speed;
			playerDirection = UP;

		}

		if (keys[DIK_S]) {

			posY = posY + speed;
			playerDirection = DOWN;
		}

		if (keys[DIK_A]) {

			posX = posX - speed;
			playerDirection = LEFT;

		}

		if (keys[DIK_D]) {

			posX = posX + speed;
			playerDirection = RIGHT;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawSprite((int)posX, (int)posY, GH[playerDirection][(int)animationCount],1.0f, 1.0f, 0.0f, WHITE);

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
