#include <Novice.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//　変数宣言

	//　自機の矩形の情報
	float playerPosX = 256.0f;
	float playerPosY = 360.0f;
	float playerWidth = 16.0f;
	float playerHeight = 64.0f;
	float playerSpeed = 7.0f;

	//　中央の矩形の情報
	float targetPosX = 638.0f;
	float targetPosY = 360.0f;
	float targetWidth = 62.0f;
	float targetHeight = 64.0f;

	//　矩形の当たり判定を管理する変数
	float playerLeftX = 0.0f;
	float playerRightX = 0.0f;
	float playerTopY = 0.0f;
	float playerBottomY = 0.0f;

	float targetLeftX = 0.0f;
	float targetRightX = 0.0f;
	float targetTopY = 0.0f;
	float targetBottomY = 0.0f;

	//　X座標が重なっているかどうかを管理する変数
	int isHitX = false;

	//　Y座標が重なっているかどうかを管理する変数
	int isHitY = false;

	//　当たっているかどうかを管理する変数
	int isTargetHit = false;

	//　リソース画像が切り替わっているかどうかを管理する処理
	int isResourceChange = false;

	//　リソース画像
	int circleWGH = Novice::LoadTexture("./Resources/Images/CircleW.png");
	int circleWHitGH = Novice::LoadTexture("./Resources/Images/CircleWHit.png");
	int circleGH = Novice::LoadTexture("./Resources/Images/Circle.png");
	int circleHitGH = Novice::LoadTexture("./Resources/Images/CircleHit.png");

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

		playerLeftX = playerPosX-playerWidth;
		playerRightX = playerPosX + playerWidth;
		playerTopY = playerPosY-playerHeight;
		playerBottomY = playerPosY + playerHeight;

		targetLeftX = targetPosX-targetWidth;
		targetRightX = targetPosX + targetWidth;
		targetTopY = targetPosY-targetHeight;
		targetBottomY = targetPosY + targetHeight;

		//　自機の矩形の移動処理
		if (keys[DIK_A]) {

			playerPosX = playerPosX - playerSpeed;

		}

		if (keys[DIK_D]) {

			playerPosX = playerPosX + playerSpeed;
		}

		if (keys[DIK_W]) {

			playerPosY = playerPosY - playerSpeed;
		}

		if (keys[DIK_S]) {

			playerPosY = playerPosY + playerSpeed;
		}


		if (keys[DIK_Q]) {
			playerWidth++;
		}
		

		//　自機の矩形の拡大、縮小の処理

		if (keys[DIK_Q]) {

			playerWidth ++ ;


		}

		if (keys[DIK_Z]) {

			playerHeight ++ ;
		}

		if (keys[DIK_E]) {

			playerWidth--;

		}

		if (keys[DIK_C]) {

			playerHeight--;

		}

		//　リソース画像を切り替える処理
		if (isResourceChange == false) {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

				isResourceChange = true;

			}
		} else {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

				isResourceChange = false;

			}

		}


		//　矩形の当たり判定
		if (targetLeftX < playerRightX && playerLeftX < targetRightX) {

			isHitX = true;

		} else {

			isHitX = false;

		}

		if (targetTopY < playerBottomY && playerTopY < targetBottomY) {

			isHitY = true;

		} else {

			isHitY = false;

		}

		if (isHitX && isHitY) {

			isTargetHit = true;

		} else {

			isTargetHit = false;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawLine(0, 360, 1280, 360, WHITE);

		Novice::DrawLine(640, 0, 640, 720, WHITE);

		if (isTargetHit) {
			if (isResourceChange) {

				Novice::DrawQuad((int)targetLeftX, (int)targetTopY,
					(int)targetRightX, (int)targetTopY,
					(int)targetLeftX, (int)targetBottomY,
					(int)targetRightX, (int)targetBottomY, 0, 0, 32, 32, circleHitGH, WHITE);

				Novice::DrawQuad((int)playerLeftX, (int)playerTopY,
					(int)playerRightX, (int)playerTopY,
					(int)playerLeftX, (int)playerBottomY,
					(int)playerRightX, (int)playerBottomY, 0, 0, 32, 32, circleHitGH, WHITE);

			} else {
				Novice::DrawQuad((int)targetLeftX, (int)targetTopY,
					(int)targetRightX, (int)targetTopY,
					(int)targetLeftX, (int)targetBottomY,
					(int)targetRightX, (int)targetBottomY, 0, 0, 32, 32, circleWHitGH, WHITE);

				Novice::DrawQuad((int)playerLeftX, (int)playerTopY,
					(int)playerRightX, (int)playerTopY,
					(int)playerLeftX, (int)playerBottomY,
					(int)playerRightX, (int)playerBottomY, 0, 0, 32, 32, circleWHitGH, WHITE);
			}
		}

		else {
			if (isResourceChange) {

				Novice::DrawQuad((int)targetLeftX, (int)targetTopY,
					(int)targetRightX, (int)targetTopY,
					(int)targetLeftX, (int)targetBottomY,
					(int)targetRightX, (int)targetBottomY, 0, 0, 32, 32, circleGH, WHITE);

				Novice::DrawQuad((int)playerLeftX, (int)playerTopY,
					(int)playerRightX, (int)playerTopY,
					(int)playerLeftX, (int)playerBottomY,
					(int)playerRightX, (int)playerBottomY, 0, 0, 32, 32, circleGH, WHITE);

			} else {
				Novice::DrawQuad((int)targetLeftX, (int)targetTopY,
					(int)targetRightX, (int)targetTopY,
					(int)targetLeftX, (int)targetBottomY,
					(int)targetRightX, (int)targetBottomY, 0, 0, 32, 32, circleWGH, WHITE);

				Novice::DrawQuad((int)playerLeftX, (int)playerTopY,
					(int)playerRightX, (int)playerTopY,
					(int)playerLeftX, (int)playerBottomY,
					(int)playerRightX, (int)playerBottomY, 0, 0, 32, 32, circleWGH, WHITE);
			}
		}


		Novice::ScreenPrintf(700, 50, "isHitX:%s", isHitX ? "true":"false");

		Novice::ScreenPrintf(700, 65, "isHitY:%s", isHitY ? "true":"false");

		Novice::ScreenPrintf(700, 80, "isTargetHit:%s", isTargetHit ? "true" : "false");
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
