#include <Novice.h>

const char kWindowTitle[] = "AL8";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//　背景画像
	int bgGH = Novice::LoadTexture("./bg.png");

	//背景の情報
	float bgY = 0.0f;
	float bgSpeed = 2.0f;
	int bgMove = true;

	//　シーン切り替えの宣言
	enum SCENE {
		FIRST_BACK,
		SECOND_BACK,
		THIRD_BACK,
	};

	int bg = FIRST_BACK;

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

		//　シーン切り替え処理
		switch (bg) {
		case FIRST_BACK:
			if (keys[DIK_SPACE]&&preKeys[DIK_SPACE] == false) {

				bg = SECOND_BACK;

			}
			break;

		case SECOND_BACK:

			//　背景の移動
			if (bgMove) {
				bgY = bgY + bgSpeed;

				if (bgY >= 720) {
					bgY = 0;
				}
			}

			if (keys[DIK_SPACE]&&preKeys[DIK_SPACE] == false) {

				bg = THIRD_BACK;

		

			}
			break;

		case THIRD_BACK:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

				bg = FIRST_BACK;
			}
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (bg) {

		case FIRST_BACK:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, RED,kFillModeSolid);
			break;

		case SECOND_BACK:
			Novice::DrawSprite(0, (int)bgY, bgGH, 1.0f, 1.0f, 0.0f, WHITE);

			Novice::DrawSprite(0, (int)bgY - 720, bgGH, 1.0f, 1.0f, 0.0f, WHITE);
			break;

		case THIRD_BACK:
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, GREEN, kFillModeSolid);
			break;
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
