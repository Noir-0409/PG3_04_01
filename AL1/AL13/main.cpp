#include <Novice.h>
#include <Math.h>

const char kWindowTitle[] = "AL1-13";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//　変数宣言

	//　自機の矩形の情報
	float playerLeftX = 240.0f;
	float playerRightX = 272.0f;
	float playerTopY = 296.0f;
	float playerBottomY = 424.0f;
	float speed = 7.0f;

	float posX = 0.0f;
	float posY = 0.0f;
	float 
	
	//　中央の矩形の情報
	float targetLeftX = 576.0f;
	float targetRightX = 704.0f;
	float targetTopY = 296.0f;
	float targetBottomY = 424.0f;
	

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

		//　自機の移動処理
		if (keys[DIK_A]) {

			playerLeftX = playerLeftX - speed;

			playerRightX = playerRightX - speed;

		}

		if (keys[DIK_D]) {

			playerLeftX = playerLeftX + speed;

			playerRightX = playerRightX + speed;

		}

		if (keys[DIK_S]) {

			playerTopY = playerTopY + speed;

			playerBottomY = playerBottomY + speed;

		}

		if (keys[DIK_W]) {

			playerTopY = playerTopY - speed;

			playerBottomY = playerBottomY - speed;

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

		//　リソース画像を切り替える処理
		if (isResourceChange == false) {
			if (keys[DIK_SPACE]&&preKeys[DIK_SPACE]==false) {

				isResourceChange = true;

			}
		} else {
			if (keys[DIK_SPACE]&&preKeys[DIK_SPACE]==false) {

				isResourceChange = false;

			}

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
			
			}
			else {
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
