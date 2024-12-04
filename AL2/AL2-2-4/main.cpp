#include <Novice.h>
#include <stdlib.h>
#include <time.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	unsigned int currentTime = (unsigned int)time(nullptr);

	srand(currentTime);

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//変数宣言

	// 弾の情報
	float posX[200] = { 0.0f };
	float posY[200] = { 0.0f };
	float speed[200] = { 50.0f };
	float radius[200] = { 0.0f };
	int isShot[200] = { false };

	// カーソルに合わせる変数
	int emitX = 0;
	int emitY = 0;

	//　乱数を管理する変数
	int emitMaxX = 51;
	int emitMinX = 25;
	int emitMaxY = 51;
	int emitMinY = 25;

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

		//　弾の出る範囲を操作する処理
		if (emitMinX >> 0) {

			if (keys[DIK_A]) {

				emitMaxX--;

			}

		}

			if (keys[DIK_D]) {

				emitMaxX++;

			}

		if (emitMinY >> 0) {

			if (keys[DIK_W]) {

				emitMaxY--;

			}

		}

			if (keys[DIK_S]) {

				emitMaxY++;

			}

		// 弾を出す処理
		for (int i = 0; i < 200; i++) {

			if (isShot[i] == false) {

				isShot[i] = true;

				speed[i] = 0;

				radius[i] = 8;

				posX[i] = (float)emitX + rand() % emitMaxX - emitMinX;

				posY[i] = (float)emitY + rand() % emitMaxY - emitMinY;

				break;

			}

		}

		// 乱数の範囲を制御する処理
		emitMinX = emitMaxX / 2;

		emitMinY = emitMaxY / 2;

		// 弾を動かす処理
		for (int i = 0; i < 200; i++) {

			if (isShot[i]) {

				posY[i] += speed[i];

				speed[i]++;

			}

			if (posY[i] >= 750) {

				isShot[i] = false;

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

		// 背景の線の描画
		Novice::DrawLine(640, 0, 640, 720, WHITE);

		Novice::DrawLine(0, 360, 1280, 360, WHITE);

		// 範囲の矩形の描画
		Novice::DrawBox(emitX - (int)emitMinX, emitY -(int) emitMinY, (int)emitMaxX, (int)emitMaxY, 0.0f, WHITE, kFillModeWireFrame);

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
