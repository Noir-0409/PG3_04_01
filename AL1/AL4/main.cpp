#include <Novice.h>

const char kWindowTitle[] = "AL1-4";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	int playerPosX = 640;
	int playerPosY = 360;
	int playerSpeed = 10;

	int bulletPosX = 0;
	int bulletPosY = 0;
	int bulletRadius = 8;
	int bulletSpeed = 10;
	bool isBulletShot = false;
	Novice::Initialize(kWindowTitle, 1280, 720);

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

		if (keys[DIK_UP]) {
			playerPosY = playerPosY - playerSpeed;
		}

		if (keys[DIK_DOWN]) {
			playerPosY = playerPosY + playerSpeed;
		}

		if (keys[DIK_LEFT]) {
			playerPosX = playerPosX - playerSpeed;
		}

		if (keys[DIK_RIGHT]) {
			playerPosX = playerPosX + playerSpeed;
		}
		//　弾の発射処理
		if (isBulletShot == false) {
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				isBulletShot = true;
				bulletPosX = playerPosX;
				bulletPosY = playerPosY;
			}
		}

	

			
		

		//　弾道計算
		if (isBulletShot == true) {
			bulletPosY -= bulletSpeed;
			if (bulletPosY <= 0) {
				bulletPosY = -200;
				isBulletShot = false;
			}
		}

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawTriangle(
			bulletPosX,
			bulletPosY - bulletRadius,

			bulletPosX - bulletRadius,
			bulletPosY + bulletRadius,

			bulletPosX + bulletRadius,
			bulletPosY + bulletRadius,
			0xFFFFFFFF, kFillModeSolid);

		if (isBulletShot) {
			Novice::DrawTriangle(
				bulletPosX, bulletPosY - bulletRadius,
				bulletPosX - bulletRadius, bulletPosY + bulletRadius,
				bulletPosX + bulletRadius, bulletPosY + bulletRadius,
				0xFFFFFFFF, kFillModeSolid
			);
		}
		Novice::DrawEllipse(playerPosX, playerPosY, 20, 20, 0.0f, 0xFFFFFFFF, kFillModeSolid);

		Novice::ScreenPrintf(0, 10, "playerposX=%d", playerPosX);
		Novice::ScreenPrintf(150, 10, "playerposY=%d", playerPosY);
		Novice::ScreenPrintf(0, 30, "bulletposX=%d", bulletPosX);
		Novice::ScreenPrintf(150, 30, "bulletposY=%d", bulletPosY);
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
