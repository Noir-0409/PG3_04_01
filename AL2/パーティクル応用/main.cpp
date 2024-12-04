#include <Novice.h>
#include <stdlib.h>
#include <time.h>



const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// 変数宣言

	// 弾の情報
	float posX[200] = { 0.0f };
	float posY[200] = { 0.0f };
	float radius[200] = { 10.0f };
	float speed[200] = { 5.0f };
	int isShot[200] = { false };

	// カーソルに合わせる変数
	int emitX = 0;
	int emitY = 0;

	// 乱数を管理する変数
	int emitMaxX = 51;
	int emitMinX = 25;
	int emitMaxY = 51;
	int emitMinY = 25;
	int emitMaxS = 11;
	int emitMinS = 5;

	// クリックを管理する変数
	int isClick = false;

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

		//rand
		unsigned int currentTime = (unsigned int)time(nullptr);
		srand(currentTime);


		// カーソルに合わせる処理
		Novice::GetMousePosition(&emitX, &emitY);

		// クリックの処理
		if (Novice::IsPressMouse(0)) {

			isClick = true;

		} else {

			isClick = false;

		}

		// 弾を出す処理
		for (int i = 0; i < 200; i++) {

			if (isShot[i] == false) {

				isShot[i] = true;

				posX[i] = 640;

				posY[i] = 360;

				speed[i] = 0;

				radius[i] = 8;

				posX[i] = posX[i] + rand() % emitMaxX - emitMinX;

				posY[i] = posY[i] + rand() % emitMinY - emitMinY;

				emitX = emitX + rand() % emitMaxX - emitMinX;

				emitY = emitY + rand() % emitMaxY - emitMinY;

				speed[i] = speed[i] + rand() % emitMaxS - emitMinS;

				break;

			}

		}

		// 弾を動かす処理
		for (int i = 0; i < 200; i++) {

			if (isShot[i]) {

				posX[i] += speed[i];

				posX[i] -= speed[i];

				posY[i] += speed[i];

				posY[i] -= speed[i];

				speed[i]++;

			}

			if (isClick) {

				posX[i] = (float)emitX;

				posY[i] = (float)emitY;

			}

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 背景の描画
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

		// 弾の描画
		for (int i = 0; i < 200; i++) {

			if (isShot[i]) {

				Novice::DrawEllipse((int)posX[i], (int)posY[i], (int)radius[i], (int)radius[i], 0.0f, WHITE, kFillModeSolid);

			}

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
