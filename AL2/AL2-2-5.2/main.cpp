#include <Novice.h>
#include <stdlib.h>
#include <time.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// 変数宣言
	const int MAX = 50;
	int posX[MAX];
	int posY[MAX];
	int radius[MAX];
	int speedX[MAX];
	int speedY[MAX];
	int isShot[MAX];
	int alpfa[MAX];

	for (int i = 0; i < MAX; i++) {

		posX[i] = 0;

		posY[i] = 0;

		speedX[i] = 0;

		speedY[i] = 0;

		radius[i] = 16;

		isShot[i] = 0;

		alpfa[i] = 0;

	}

	int keepPosX = 640;
	int keepPosY = 360;

	// マウスカーソルに合わせる変数
	int emitX = 0;
	int emitY = 0;

	// リソース画像
	int particleGH = Novice::LoadTexture("./Resources/particle.jpg");

	int GetMoucePosition(int* posX, int* posY);

	// 透明度
	int color = 0xffffff64;

	enum Blend {

		Normal,
		Add,
		Subtract,
		None,
		BlendBlendMode

	};

	int scene = Normal;

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

		// カーソルに合わせる処理
		Novice::GetMousePosition(&emitX, &emitY);

		for (int i = 0; i < MAX; i++) {

			// マウスがクリックされているか
			if (Novice::IsTriggerMouse(0)) {

				keepPosX = emitX;

				keepPosY = emitY;

			}

			// パーティクルを発生させる処理

			if (isShot[i] == 0) {

				posX[i] = keepPosX;

				posY[i] = keepPosY;

				speedX[i] = rand() % 5 - 2;

				speedY[i] = rand() % 5 - 2;

				isShot[i] = true;

				alpfa[i] = 40;

			}

		}


			// パーティクルを動かす処理

		for (int i = 0; i < MAX; i++) {

			if (isShot[i]) {

				posX[i] += speedX[i];

				posY[i] += speedY[i];

				alpfa[i]--;

			}

			// 値をリセットする処理

			if (alpfa[i] <= 5) {

				isShot[i] = 0;

			}

		}

		// シーン切り替え処理
		if (keys[DIK_1] && preKeys[DIK_1] == false) {

			scene = Normal;

		}

		if (keys[DIK_2] && preKeys[DIK_2] == false) {

			scene = Add;

		}

		if (keys[DIK_3] && preKeys[DIK_3] == false) {

			scene = Subtract;

		}

		if (keys[DIK_4] && preKeys[DIK_4] == false) {

			scene = None;
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// シーン切り替え処理
		switch (scene) {

		case Normal:

			Novice::SetBlendMode(BlendMode::kBlendModeNormal);

			Novice::ScreenPrintf(700, 10, "1 Normal");

			break;

		case Add:

			Novice::SetBlendMode(BlendMode::kBlendModeAdd);

			Novice::ScreenPrintf(700, 10, "2 Add");

			break;

		case Subtract:

			Novice::SetBlendMode(BlendMode::kBlendModeSubtract);

			Novice::ScreenPrintf(700, 10, "3 Subtract");

			break;

		case None:

			Novice::SetBlendMode(BlendMode::kBlendModeNone);

			Novice::ScreenPrintf(700, 10, "4 None");

			break;

		}

		// デバッグ用の文字
		Novice::ScreenPrintf(10, 10, "0:None");

		Novice::ScreenPrintf(10, 30, "1:Normal");

		Novice::ScreenPrintf(10, 50, "2:Add");

		Novice::ScreenPrintf(10, 70, "3:Subtract");

		Novice::ScreenPrintf(10, 90, "4:Multiply");

		Novice::ScreenPrintf(10, 110, "5:Screen");

		// 自機の画像
		for (int i = 0; i < MAX; i++) {

			Novice::DrawSprite(posX[i] - 32, posY[i] - 32, particleGH, 1.0f, 1.0f, 0.0f, color);

			Novice::ScreenPrintf(10, 130, "alpfa= %d",alpfa[i]);
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
