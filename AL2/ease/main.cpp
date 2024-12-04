#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>


float posX[6] = { 0.0f };
float posY[6] = { 60.0f,180.0,300.0f,420.0f,540.0f,660.0f };
float leftTopX[6] = { 0.0f };
float leftTopY[6] = { 0.0f };
float width = 1280.0f;
float height = 120.0f;

float startX[6] = { -1280.0f,-1580.0f,-1880.0f,-2180.0f,-2480.0f,-2780.0f };
float endX = 640.0f;
float frameX = 0.0f;
float endFrameX = 180.0f;

int moveX = false;

float easeOutBackSine(float x) {

	const double c1 = 1.70158;

	const double c3 = c1 + 1;

	return (float)1 + (float)c3 * (float)pow(x - 1, 3)  + (float)c1 * (float)pow(x - 1, 2);

}

float easeOutBack(float x) {

	return easeOutBackSine(x = (frameX / endFrameX));

}



const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

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

		
		for (int i = 0; i < 6; i++) {

			leftTopX[i] = posX[i] - width / 2;
			leftTopY[i] = posY[i] - height / 2;
		
		}

		//自機を動かす処理
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

			moveX = true;

			frameX = 0;

		}

		if (moveX) {

			frameX++;

		}

		if (frameX >= endFrameX) {

			moveX = false;

		}

		for (int i = 0; i < 6; i++) {

			posX[i] = startX[i] + (endX - startX[i]) * easeOutBack(frameX / endFrameX);

		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawLine(0, 360, 1280, 360, BLACK);

		Novice::DrawLine(640, 0, 640, 720, BLACK);

		// 自機の描画
		for (int i = 0; i < 6; i++) {

			Novice::DrawBox((int)leftTopX[i], (int)leftTopY[i], (int)width, (int)height, 0.0f, 0x0000cdff, kFillModeSolid);

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
