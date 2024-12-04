#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

//変数宣言
float posX[2] = { 0.0f,0.0f }; //自機のX座標
float posY[2] = { 100.0f,300.0f }; //自機のY座標
float startX = 100.0f;		//開始位置
float endX = 1180.0f;		//終了位置
float frameX = 0.0f;		//現在の位置
float endFrameX = 90.0f;	//全体の時間

int isMoveX = false;

// 残像の情報
const int afterImageLength = 20;
int isDraw1[afterImageLength] = {};
int afterImageX1[afterImageLength] = {};
int isDraw2[afterImageLength] = {};
int afterImageX2[afterImageLength] = {};
int timer = 0;

// イージング関数の作成
float easeInSine(float x) {

	return 1 - cosf((x * (float)M_PI) / 2);

}

float easeIn(float x) {

	return easeInSine(x = (frameX / endFrameX));

}

float easeOutSine(float x) {

	return sinf((x * (float)M_PI) / 2);

}

float easeOut(float x) {

	return easeOutSine(x = (frameX / endFrameX));

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

		// 自機や残像を動かす処理
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

			isMoveX = true;

			frameX = 0;

			timer = 0;

			for (int i = 0; i < afterImageLength; i++) {

				isDraw1[i] = 0;

				isDraw2[i] = 0;

			}

		}

		if (isMoveX) {

			frameX++;

			timer++;

		}

		if (frameX >= endFrameX) {

			isMoveX = false;

		}

		// 残像を作成する処理
		if (timer == 5) {

			timer = 0;

			for (int i = 0; i < afterImageLength; i++) {

				if (isDraw1[i] == 0) {

					afterImageX1[i] = (int)posX[0];



					isDraw1[i] = 1;

					break;
				}

			}

			for (int i = 0; i < afterImageLength; i++) {

				if (isDraw2[i] == 0) {

					afterImageX2[i] = (int)posX[1];



					isDraw2[i] = 1;

					break;
				}

			}

		}

		// 自機のイージング処理
		posX[0] = startX + (endX - startX) * easeIn(frameX / endFrameX);

		posX[1] = startX + (endX - startX) * easeOut(frameX / endFrameX);

		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		// 背景の描画
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xb0c4deff,kFillModeSolid);

		// 残像の描画
		for (int i = 0; i < afterImageLength; i++) {

			if (isDraw1[i] == (int)true) {

				Novice::DrawBox(afterImageX1[i], 100, 30, 30, 0.0f, WHITE, kFillModeSolid);

			}

			if (isDraw2[i] == (int)true) {

				Novice::DrawBox(afterImageX2[i], 300, 30, 30, 0.0f, WHITE, kFillModeSolid);

			}

		}

		// 自機の描画
		Novice::DrawBox((int)posX[0], 100, 30, 30, 0.0f, BLACK, kFillModeSolid);

		Novice::DrawBox((int)posX[1], 300, 30, 30, 0.0f, BLACK, kFillModeSolid);

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
