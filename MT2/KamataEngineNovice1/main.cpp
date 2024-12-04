#include <Novice.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	float sarclePosX = 640.0f;
	float sarclePosY = 360.0f;
	float sarcleRadius = 30.0f;
	float sarcleAura[3] = { 30.0f,30.0f,30.0f };
	float sarcleAuraSpeed = 7.0f;
	float attackCount = 300.0f;

	int isAttack = false;
	//int isBurn[3] = { false };

	// 変数宣言
	const int MAX = 300;
	int p_posX[MAX];
	int p_posY[MAX];
	int p_radius[MAX];
	int p_speedX[MAX];
	int p_speedY[MAX];
	int p_isShot[MAX];
	int p_alpfa[MAX];

	for (int i = 0; i < MAX; i++) {

		p_posX[i] = 0;

		p_posY[i] = 0;

		p_speedX[i] = 0;

		p_speedY[i] = 0;

		p_radius[i] = 16;

		p_isShot[i] = 0;

		p_alpfa[i] = 0;

	}

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

		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

			isAttack = true;

			attackCount = 300;

			for (int i = 0; i < 3; i++) {

				sarcleAura[i] = 30;

			}

		}

		for (int i = 0; i < MAX; i++) {

			if (isAttack) {

				attackCount--;

			}

		}

		if (attackCount <= 270) {

			sarcleAura[0] += sarcleAuraSpeed;

		}

		if (attackCount <= 180) {

			sarcleAura[1] += sarcleAuraSpeed;

		}

		if (attackCount <= 90) {

			sarcleAura[2] += sarcleAuraSpeed;

		}



		if (attackCount == 0) {

			isAttack = false;

		}

		for (int i = 0; i < MAX; i++) {

			if (p_isShot[i] == 0) {

				p_posX[i] = (int)sarclePosX;

				p_posY[i] = (int)sarclePosY;

				p_speedX[i] = rand() % 11 - 5;

				p_speedY[i] = rand() % 11 - 5;

				p_isShot[i] = true;

				p_alpfa[i] = 120;

			}

			// パーティクルを動かす処理

			if (p_isShot[i]) {

				p_posX[i] += p_speedX[i];

				p_posY[i] += p_speedY[i];

				p_alpfa[i]--;

			}


			if (p_alpfa[i] <= 5) {

				p_isShot[i] = 0;

			}

	}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse((int)sarclePosX, (int)sarclePosY, (int)sarcleRadius, (int)sarcleRadius, 0.0f, WHITE, kFillModeSolid);

		if (isAttack) {

			for (int i = 0; i < 3; i++) {

				Novice::DrawEllipse((int)sarclePosX, (int)sarclePosY, (int)sarcleAura[i], (int)sarcleAura[i], 0.0f, WHITE, kFillModeWireFrame);

			}

		}

		for (int i = 0; i < MAX; i++) {

			Novice::DrawEllipse(p_posX[i], p_posY[i], p_radius[i], p_radius[i], 0.0f, 0xffffff64, kFillModeSolid);

		}

		Novice::ScreenPrintf(10, 10, "%f", attackCount);

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
