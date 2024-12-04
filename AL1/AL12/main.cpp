#include <Novice.h>

const char kWindowTitle[] = "AL1-12";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//　変数宣言

	//　自機の情報
	float playerPosX = 100.0f;
	float playerPosY = 569.0f;
	float playerWidth = 25.0f;
	float playerHeight = 25.0f;
	float playerSpeed = 6.0f;
	float playerScreen = 0.0f;
	float playerPosX2 = 0.0f;

	//　線の情報
	float linePosX[2] = { 800.0f , 800.0f };
	float linePosY[2] = { 0.0f , 720.0f };
	float lineSpeed = 8.0f;

	//　スクロール座標の情報
	float scrollX = 0.0f;
	float scrollSpeed = 8.0f;



	//　背景の情報
	float bgPosX[4] = { 0.0f , 1280.0f , 2560.0f , 3840.0f };
	float bgPosY[4] = { 0.0f , 0.0f , 0.0f , 0.0f };

	//　リソース画像
	int bgGH[4] = {
		{Novice::LoadTexture("./Resources/Images/bg1.png") },
		{Novice::LoadTexture("./Resources/Images/bg2.png") },
		{Novice::LoadTexture("./Resources/Images/bg3.png") },
		{Novice::LoadTexture("./Resources/Images/bg4.png") }
	};

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

		

		//　自機の移動処理

		if (keys[DIK_A]) {

			playerPosX = playerPosX - playerSpeed;

		}

		if (keys[DIK_D]) {

			playerPosX = playerPosX + playerSpeed;

		}

		//　線の移動処理

		if (keys[DIK_LEFT]) {

			linePosX[0] = linePosX[0] - lineSpeed;

			linePosX[1] = linePosX[1] - lineSpeed;

		}

		if (keys[DIK_RIGHT]) {

			linePosX[0] = linePosX[0] + lineSpeed;

			linePosX[1] = linePosX[1] + lineSpeed;

		}

		if (scrollX >= 3840) {

			if (keys[DIK_A] && playerPosX == linePosX[0] - playerWidth) {

				scrollX = scrollX - scrollSpeed;

			}
		}

		//　自機が線よりも右側に行けなくする処理
		if (scrollX < 1280 * 3) {//
			if (playerPosX2 > linePosX[0]) {

				linePosX[0] = playerPosX2;

				linePosX[1] = playerPosX2;
			}
		}


		if (scrollX >= 1) {
			if (scrollX < 1280 * 3) {
				//右ラインについたら位置を修正する
				playerPosX = linePosX[0] - playerWidth;
				playerPosX = linePosX[1] - playerWidth;
			} else {
				//
				linePosX[0] = linePosX[0];
				linePosX[1] = linePosX[1];
			}
		}







		//　線が矩形に触れると左側に行けなくする処理
		if (scrollX < 1280 * 3) {//
			if (playerPosX == linePosX[0] - playerWidth) {

				lineSpeed = lineSpeed * 0;

			}
		}

		lineSpeed=8;
		

		

		//　線が画面外に出ないようにする処理

		if (linePosX[0] >= 1280) {

			linePosX[0] = linePosX[0] - lineSpeed;

			linePosX[1] = linePosX[1] - lineSpeed;

		}

		if (linePosX[0] <= 0) {

			linePosX[0] = linePosX[0] + lineSpeed;

			linePosX[1] = linePosX[1] + lineSpeed;

		}

		

		//　スクロール座標の移動処理

		if (keys[DIK_D]) {

			if (playerPosX2 >= linePosX[0]) {

				if (scrollX >= 0) {

					scrollX = scrollX + scrollSpeed;
				
				}
			}
		}

		if (keys[DIK_A]) {

			if (playerPosX2 >= linePosX[0]) {

				if (scrollX <= 3839) {

					scrollX = scrollX - scrollSpeed;
				
				}
			}
		}

		if (scrollX <= 0) {

			scrollX = 0;

		}

		if (scrollX >= 3840) {

			scrollX = 3840;

			lineSpeed = 0;

		}

		playerScreen = playerPosX + scrollX;

		playerPosX2 = playerPosX + playerWidth;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawSprite((int)bgPosX[0] - (int)scrollX, (int)bgPosY[0], bgGH[0], 1.0f, 1.0f, 0.0f, WHITE);

		Novice::DrawSprite((int)bgPosX[1] - (int)scrollX, (int)bgPosY[1], bgGH[1], 1.0f, 1.0f, 0.0f, WHITE);

		Novice::DrawSprite((int)bgPosX[2] - (int)scrollX, (int)bgPosY[2], bgGH[2], 1.0f, 1.0f, 0.0f, WHITE);

		Novice::DrawSprite((int)bgPosX[3] - (int)scrollX, (int)bgPosY[3], bgGH[3], 1.0f, 1.0f, 0.0f, WHITE);

		Novice::DrawBox((int)playerPosX, (int)playerPosY, (int)playerWidth, (int)playerHeight, 0.0f, BLUE, kFillModeSolid);

		Novice::DrawLine((int)linePosX[0], (int)linePosY[0], (int)linePosX[1], (int)linePosY[1], RED);

		Novice::ScreenPrintf(10, 100, "scroll X:%f", scrollX);

		Novice::ScreenPrintf(10, 150, "playerPosX:%f", playerPosX+scrollX);

		Novice::ScreenPrintf(10, 200, "playerScreenX:%f", playerPosX );

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
