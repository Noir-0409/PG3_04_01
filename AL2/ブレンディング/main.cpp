#include <Novice.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// 変数宣言

	int posX = 0;
	int posY = 0;
	int r = 300;

	// 透明度
	int frameColor = 0xffffff64;
	int color = 0xffffffff;
	int alpfa = 0xffffff00;

	enum Blend {

		Normal,
		Add,
		Subtract,
		None,
		BlendBlendMode

	};

	int scene = Normal;

	int particle = Novice::LoadTexture("./particle.png");

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

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

		// マウスカーソルに合わせる処理
		Novice::GetMousePosition(&posX, &posY);

		// 透明度を変える処理
		if (keys[DIK_DOWN]) {

				frameColor--;

				if (frameColor <= alpfa) {

					frameColor=0xffffff00;

				}

			}

			if (keys[DIK_UP]) {

				frameColor++;

				if (frameColor >= color) {

					frameColor = 0xffffffff;

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

		// 背景の画像の描画
		Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

		// 背景の線の描画
		Novice::DrawLine(640, 0, 640, 720, WHITE);

		Novice::DrawLine(0, 360, 1280, 360, WHITE);

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

		// 画像の描画
		Novice::DrawSprite(440 - r, 360 - r, particle, 1.0f, 1.0f, 0.0f, frameColor);

		Novice::DrawSprite(640 - r, 360 - r, particle, 1.0f, 1.0f, 0.0f, frameColor);

		Novice::DrawSprite(840 - r, 360 - r, particle, 1.0f, 1.0f, 0.0f, frameColor);

		Novice::DrawSprite(posX - r, posY - r, particle, 1.0f, 1.0f, 0.0f, frameColor);

		//	デバッグ用の文字
		Novice::ScreenPrintf(10, 10, "1 Normal  2 Add  3 Subtract  4 None");

		Novice::ScreenPrintf(10, 30, "color=%x", color);

		Novice::ScreenPrintf(10, 50, "alpfa=%x", alpfa);

		Novice::ScreenPrintf(10, 70, "frameColor=%x", frameColor);

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