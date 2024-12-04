#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "LC1C_20_タムラアツキ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//変数宣言

	// 自機の情報
	float playerX = 100.0f;
	float playerY = 100.0f;
	float playerR = 50.0f;
	float playerSpeed = 10.0f;
	
	// 自機の各頂点の座標
	float playerLeft = 0.0f;
	float playerRight = 0.0f;
	float playerTop = 0.0f;
	float playerBottom = 0.0f;

	// 弾の情報
	float posX[200] = { 0.0f };
	float posY[200] = { 0.0f };
	float speed[200] = { 0.0f };
	float radius[200] = { 0.0f };
	int isShot[200] = { false };

	// 障害物の情報
	float ovjX = 640.0f;
	float ovjY = 360.0f;
	float ovjR = 100.0f;

	// 障害物の各頂点の座標
	float ovjLeft = 0.0f;
	float ovjRight = 0.0f;
	float ovjTop = 0.0f;
	float ovjBottom = 0.0f;

	//　乱数を管理する変数
	int emitMaxX = 1281;
	int emitMinX = 640;
	int emitMaxY = 11;
	int emitMinY = 5;

	// シェイクの乱数を管理する変数
	int randX = 0;
	int randY = 0;

	// 揺らす時間
	float randTimer = 120.0f;

	// 乱数の範囲
	int shakeX = 80;
	int shakeY = 80;

	int isShake = false;

	// 当たり判定を管理する変数
	int isHitX = false;;
	int isHitY = false;;
	int isHit = false;

	// 透明度
	int frameColor = 0xffffff64;
	int color = 0xffffffff;
	int alpfa = 0xffffff00;

	enum Blend {

		Normal,
		Add,
		Subtract,
		BlendBlendMode

	};

	int scene = Normal;

	int particle = Novice::LoadTexture("./particle.png");


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

		// 各頂点の座標
		playerLeft = playerX - playerR;

		playerRight = playerX + playerR;

		playerTop = playerY - playerR;

		playerBottom = playerY + playerR;

	

			ovjLeft = ovjX - ovjR;

			ovjRight = ovjX + ovjR;

			ovjTop = ovjY - ovjR;

			ovjBottom = ovjY + ovjR;

		// 当たり判定の処理
		

			if (ovjLeft < playerRight && playerLeft < ovjRight) {

				isHitX = true;

			} else {

				isHitX = false;

			}

			if (ovjTop < playerBottom && playerTop < ovjBottom) {

				isHitY = true;

			} else {

				isHitY = false;

			}

			if (isHitX && isHitY) {

				isHit = true;

			} else {

				isHit = false;

			}

			if (isHit) {

				isShake = true;

				randTimer = 120;

				shakeX = 80;

				shakeY = 80;

		}

			if (isShake) {

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

			// 止まった時元の位置に戻る処理

			if (randTimer == 0) {

				isShake = false;
				
				randX = 0;

				randY = 0;

			}

		// 弾を出す処理
		for (int i = 0; i < 200; i++) {

			if (isShot[i] == false) {

				isShot[i] = true;

				posX[i] = 640;

				posY[i] = 0;

				speed[i] = 5;

				radius[i] = 8;

				posX[i] = posX[i] + rand() % emitMaxX - emitMinX;

				posY[i] = posY[i] + rand() % emitMaxY - emitMinY;

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

			}

			if (posY[i] >= 750) {

				isShot[i] = false;

			}

		}

		// 自機の移動処理
		if (keys[DIK_A]) {

			playerX -= playerSpeed;

		}

		if (keys[DIK_D]) {

			playerX += playerSpeed;

		}

		if (keys[DIK_W]) {

			playerY -= playerSpeed;

		}

		if (keys[DIK_S]) {

			playerY += playerSpeed;

		}

		// 透明度を変える処理
		if (keys[DIK_DOWN]) {

			frameColor--;

			if (frameColor <= alpfa) {

				frameColor = 0xffffff00;

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

		// リセット処理

		for (int i = 0; i < 200; i++) {

			if (keys[DIK_R] && preKeys[DIK_R] == false) {

				scene = Normal;

				playerX = 100;

				playerY = 100;

				frameColor = 0xffffff64;

				isShake = false;

				randX = 0;

				randY = 0;

				isShot[i] = false;

			}

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

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


		}

		// 弾の描画
		for (int i = 0; i < 200; i++) {

			if (isShot[i]) {

				Novice::DrawSprite((int)posX[i], (int)posY[i], particle, 0.05f, 0.05f, 0.0f, frameColor);

			}

		}

		

			Novice::DrawBox((int)ovjLeft+randX, (int)ovjTop+randY, (int)ovjR*2, (int)ovjR*2, 0.0f, 0xffffffff, kFillModeSolid);

		

		

			Novice::DrawBox((int)playerX, (int)playerY, (int)playerR, (int)playerR, 0.0f, BLUE, kFillModeSolid);
	

	
		Novice::ScreenPrintf(10, 10, "1 Normal  2 Add  3 Subtract ");

		Novice::ScreenPrintf(10, 30, "move WASD");

		Novice::ScreenPrintf(10, 50, "particle transparency change UP or DOWN");

		Novice::ScreenPrintf(10, 70, "reset R");

	
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
