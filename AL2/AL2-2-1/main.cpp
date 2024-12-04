#include <Novice.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 500, 500);

	// 変数宣言

	int size_map_x = 32; //マップチップXサイズ
	int size_map_y = 32; //マップチップYサイズ

	int num_map_y = 20; //32*20
	int num_map_x = 20; //32*20

	// プレイヤーの情報
	int posX = 0;
	int posY = 0;
	float width = 20.0f;
	float height = 20.0f;

	// 乱数の情報
	int randX = 0;
	int randY = 0;
	int bgRandX = 0;
	int bgRandY = 0;

	// 揺らす時間
	float randTimer = 120.0f;

	//　乱数の範囲
	int shakeX = 80;
	int shakeY = 80;
	int bgShakeX = 80;
	int bgShakeY = 80;

	int whiteGH = Novice::LoadTexture("./white.png");

	int isPressSpace = false;

	int isPressEnter = false;

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

		// マウスカーソルに合わせる処理
		Novice::GetMousePosition(&posX, &posY);

		//　フラグを切り替える処理
		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

			isPressSpace = true;

			randTimer = 120;

			shakeX = 80;

			shakeY = 80;

		}

		if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

			isPressEnter = true;

			randTimer = 120;

			bgShakeX = 80;

			bgShakeY = 80;

		}

		// プレイヤーのシェイクを起こす処理
		if (isPressSpace) {

			randTimer--;

			shakeX--;

			shakeY--;

			if (randTimer >= 1) {

				if (shakeX >= 1 && shakeY >= 1) {

					randX = rand() % (shakeX + 1) - (shakeX / 2);

					randY = rand() % (shakeY + 1) - (shakeY / 2);

				}

			}

		}

		// 背景のシェイクを起こす処理
		if (randTimer == 0) {

			isPressSpace = false;
		
		}


		if (isPressEnter) {

			randTimer--;

			bgShakeX--;

			bgShakeY--;

			if (randTimer >= 1) {

				if (bgShakeX >= 1 && bgShakeY >= 1) {

					bgRandX = rand() % (bgShakeX + 1) - (bgShakeX / 2);

					bgRandY = rand() % (bgShakeY + 1) - (bgShakeY / 2);

				}

			}

		}
		if (randTimer == 0) {
		
			isPressEnter = false;
		
		}
		  
		// 止まった時元の位置に戻る処理

		if (randTimer==0) {

			randX = 0;

			randY = 0;

			bgRandX = 0;

			bgRandY = 0;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// マップの描画
		for (int y = -2; y < num_map_y; y++) {

			for (int x = -2; x < num_map_x; x++) {


				Novice::DrawSprite(x * size_map_y + bgRandX, y * size_map_x + bgRandY, whiteGH, 4.0f, 4.0f, 0.0f, WHITE);

				
			}
		}

		//　プレイヤーの描画
		Novice::DrawEllipse(posX + randX, posY + randY, (int)width, (int)height, 0.0f, BLACK, kFillModeSolid);

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
