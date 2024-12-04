#include <Novice.h>
#include <Math.h>

const char kWindowTitle[] = "AL5";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	//　変数宣言
	
	// 自機の情報
	float playerPosX = 500.0f;
	float playerPosY = 500.0f;
	float playerRadius = 20.0f;
	float playerSpeed = 12.0f;

	//　敵機の情報
	float enemyPosX = 100.0f;
	float enemyPosY = 100.0f;
	float enemyRadius = 30.0f;
	float enemySpeed = 5.0f;
	int isEnemyAlive = true;
	int isEnemyRespawnTimer = 120;

	//　弾の情報
	float bulletPosX = 0.0f;
	float bulletPosY = 0.0f;
	float bulletSpeed = 20.0f;
	float bulletRadius = 10.0f;
	int isBulletShot = false;

	//　中間変数
	float bullet2enemyX = 0.0f;
	float bullet2enemyY = 0.0f;
	float bullet2enemy = 0.0f;

	//　爆発エフェクト
	int enemyExplosionGH = Novice::LoadTexture("./explode.png");

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

		//　自機の挙動
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

		//　自機が範囲外に出ない様にする処理
		if (playerPosY >= 710)
			playerPosY = playerPosY - 12;

		if (playerPosY <= 10)
			playerPosY = playerPosY + 12;

		if (playerPosX >= 1270)
			playerPosX = playerPosX - 12;

		if (playerPosX <= 10)
			playerPosX = playerPosX + 12;

		//　敵機が生存している時の挙動
		if (isEnemyAlive) {
			enemyPosX = enemyPosX + enemySpeed;
			if (enemyPosX >= 1255) {
				enemySpeed *= -1;
			}


			else if (enemyPosX <= 25) {
				enemySpeed *= -1;
			}
		}


		//　弾の発射処理
		if(isBulletShot==false)
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				isBulletShot = true;
				bulletPosX = playerPosX;
				bulletPosY = playerPosY;
			}

		//　弾道計算
		if (isBulletShot) {
			bulletPosY = bulletPosY - bulletSpeed;
			if (bulletPosY <= 0) {
				bulletPosY = -200;
				isBulletShot = false;
			}
		}

		//　当たり判定
		if (isEnemyAlive && isBulletShot) {
			bullet2enemyX = enemyPosX - bulletPosX;
			bullet2enemyY = enemyPosY - bulletPosY;
			bullet2enemy = sqrtf((bullet2enemyX) * (bullet2enemyX)+(bullet2enemyY) * (bulletPosY));

			if (enemyRadius + bulletRadius >= bullet2enemy) {
				isEnemyAlive = false;
				isBulletShot = false;
			}
		}

		//　敵機のリスポーン処理
		if (isEnemyAlive) {
			isEnemyRespawnTimer--;
			if (isEnemyRespawnTimer <= 0) {
				isEnemyAlive = true;
				isEnemyRespawnTimer = 120;
			}
		}

		//　敵機の爆発処理
		if (isEnemyAlive) {
			isEnemyRespawnTimer--;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse((int)playerPosX, (int)playerPosY, (int)playerRadius, (int)playerRadius, 0.0f, 0xFFFFFFFF, kFillModeSolid);

		Novice::DrawEllipse((int)enemyPosX, (int)enemyPosY, (int)enemyRadius, (int)enemyRadius, 0.0f, BLUE, kFillModeSolid);

		if (isBulletShot)
			Novice::DrawTriangle((int)bulletPosX,
				(int)bulletPosY - (int)bulletRadius,

				(int)bulletPosX - (int)bulletRadius,
				(int)bulletPosY + (int)bulletRadius,

				(int)bulletPosX + (int)bulletRadius,
				(int)bulletPosY + (int)bulletRadius,
				0xFFFFFFFF, kFillModeSolid);

		Novice::DrawEllipse((int)bulletPosX, (int)bulletPosY, (int)bulletRadius, (int)bulletRadius, 0.0f, 0x00000000, kFillModeWireFrame);
		
		if (isEnemyRespawnTimer <= 120 || isEnemyRespawnTimer >= 75) {
			Novice::DrawSprite(
				(int)enemyPosX - (int)enemyRadius,
				(int)enemyPosY - (int)enemyRadius,
				enemyExplosionGH, 1.0f, 1.0f, 0.0f, 0xFFFFFFFF);
		}

		Novice::ScreenPrintf(0, 10, "PlayerPosX=%f", playerPosX);
		Novice::ScreenPrintf(200, 10, "PlayerPosY=%f", playerPosY);
		Novice::ScreenPrintf(0, 30, "bulletPosX=%f", bulletPosX);
		Novice::ScreenPrintf(200, 30, "bulletPosY=%f", bulletPosY);
		Novice::ScreenPrintf(0, 50, "enemyRespawn=%f", isEnemyRespawnTimer);
		Novice::ScreenPrintf(200, 50, "enemyAlive=%f", isEnemyAlive);

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
