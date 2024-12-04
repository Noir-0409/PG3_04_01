#include <Novice.h>
#include <Math.h>

const char kWindowTitle[] = "楽園からの逃亡";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	
	//変数宣言

	//自機の情報
	float playerPosX = 640.0f;
	float playerPosY = 500.0f;
	float playerRadius = 45.0f;
	float playerSpeed = 12.0f;
	int isPlayerAlive = true;
	int playerRespawnTimer = 3;

	//弾の情報
	float bulletPosX = 0.0f;
	float bulletPosY = 0.0f;
	float bulletSpeed = 20.0f;
	float bulletRadius = 20.0f;
	int isBulletShot = false;

	//　敵機の情報
	float enemyPosX = 640.0f;
	float enemyPosY = 120.0f;
	float enemyRadius = 60.0f;
	float enemySpeed = 8.0f;
	int isEnemyAlive = true;
	int enemyRespawnTimer = 5;

	//　敵機の弾の情報
	float enemyBulletPosX = 0.0f;
	float enemyBulletPosY = 0.0f;
	float enemyBulletSpeed = 25.0f;
	float enemyBulletRadius = 25.0f;
	int enemyBulletShot = false;
	int enemyBulletTimer = 40;

	//　砲台の情報
	float leftCanonPosX = 30.0f;
	float overCanonPosY = 390.0f;
	float centerCanonPosY = 540.0f;
	float underCanonPosY = 690.0f;
	float canonRadius = 30.0f;
	int isCanonAlive = true;

	//　砲台の弾の情報
	float canonBulletPosX = 0.0f;
	float canonBulletPosY = 0.0f;
	float canonBulletSpeed = 6.0f;
	float canonBulletRadius = 25.0f;
	int canonBulletTimer = 150;
	int canonBulletShot = false;

	//　中間変数
	float player2enemyX = 0.0f;
	float player2enemyY = 0.0f;
	float player2enemy = 0.0f;

	float bullet2enemyX = 0.0f;
	float bullet2enemyY = 0.0f;
	float bullet2enemy = 0.0f;

	float bullet2canonX = 0.0f;
	float bullet2canonY = 0.0f;
	float bullet2canon = 0.0f;

	float player2canonX = 0.0f;
	float player2canonY = 0.0f;
	float player2canon = 0.0f;

	float enemyBullet2playerX = 0.0f;
	float enemyBullet2playerY = 0.0f;
	float enemyBullet2player = 0.0f;

	float canonBullet2playerX = 0.0f;
	float canonBullet2playerY = 0.0f;
	float canonBullet2player = 0.0f;

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
		
		// 自機の挙動
		if (keys[DIK_W]) {
			playerPosY = playerPosY - playerSpeed;
		}

		if (keys[DIK_S]) {
			playerPosY = playerPosY + playerSpeed;
		}

		if (keys[DIK_A]) {
			playerPosX = playerPosX - playerSpeed;
		}

		if (keys[DIK_D]) {
			playerPosX = playerPosX + playerSpeed;
		}


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

		//　自機が画面外に出ない様にする処理
		if (playerPosY >= 690) {
			playerPosY = playerPosY - 12;
		}

		if (playerPosY <= 40) {
			playerPosY = playerPosY + 12;
		}

		if (playerPosX >= 1245) {
			playerPosX = playerPosX - 12;
		}

		if (playerPosX <= 35) {
			playerPosX = playerPosX + 12;
		}

		//　弾の発射処理
		if (isBulletShot == false)
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				isBulletShot = true;
				bulletPosX = playerPosX;
				bulletPosY = playerPosY;
			}

		//　弾道計算
		if (isBulletShot) {
			bulletPosY = bulletPosY - bulletSpeed;
			if (bulletPosY <= 0) {
				bulletPosY = 0;
				isBulletShot = false;
			}
		}

		//　敵機の弾の発射処理
		if (enemyBulletShot == false)
			if (isEnemyAlive == 1) {
				enemyBulletShot = true;
				enemyBulletPosX = enemyPosX;
				enemyBulletPosY = enemyPosY;
			}

		//　敵機の弾道計算
		if (enemyBulletShot) {
			enemyBulletPosY = enemyBulletPosY + enemyBulletSpeed;
			if (enemyBulletPosY >= 720) {
				enemyBulletPosY = enemyPosY;
				enemyBulletShot = false;
			}
		}

		//　敵機の弾のインターバル
		if (!isEnemyAlive) {
			enemyBulletTimer--;
			if (enemyBulletTimer <= 0) {
				enemyBulletShot = true;
				enemyBulletTimer = 90;
			}
		}

		//　敵機が生存している時の挙動
		if (isEnemyAlive)
			enemyPosX = enemyPosX + enemySpeed;

		if (enemyPosX >= 1225) {
			enemySpeed *= -1;
		}

		else if (enemyPosX <= 50) {
			enemySpeed *= -1;
		}

		//　自機のリスポーン処理
		if (!isPlayerAlive) {
			playerRespawnTimer--;
			if (playerRespawnTimer <= 0) {
				isPlayerAlive = true;
				playerRespawnTimer = 3;
			}
		}

		//　敵機のリスポーン処理
		if (isEnemyAlive) {
			enemyRespawnTimer--;
			if (enemyRespawnTimer <= 0) {
				isEnemyAlive = true;
				enemyRespawnTimer = 1;
			}
		}

		//　左上の砲台の弾の発射処理
		if (canonBulletShot == false)
			if (isCanonAlive == 1) {
				canonBulletShot = true;
				canonBulletPosX = leftCanonPosX;
				canonBulletPosY = overCanonPosY;
			}

		if (canonBulletShot) {
			canonBulletPosX = canonBulletPosX + canonBulletSpeed;
			if (canonBulletPosX >= 1250) {
				canonBulletPosX = 0;
				canonBulletShot = false;
			}
		}

		if (!isCanonAlive) {
			canonBulletTimer--;
			if (canonBulletTimer <= 0) {
				canonBulletShot = true;
				canonBulletTimer = 12;
			}
		}

		//　左中の砲台の弾の発射処理
		if (canonBulletShot == false)
			if (isCanonAlive == 1) {
				canonBulletShot = true;
				canonBulletPosX = leftCanonPosX;
				canonBulletPosY = centerCanonPosY;
			}

		if (canonBulletShot) {
			canonBulletPosX = canonBulletPosX + canonBulletSpeed;
			if (canonBulletPosX >= 1250) {
				canonBulletPosX = 0;
				canonBulletShot = false;
			}
		}

		if (!isCanonAlive) {
			canonBulletTimer--;
			if (canonBulletTimer <= 0) {
				canonBulletShot = true;
				canonBulletTimer = 16;
			}
		}

		//　左下の砲台の弾の発射処理
		if (canonBulletShot == false)
			if (isCanonAlive == 1) {
				canonBulletShot = true;
				canonBulletPosX = leftCanonPosX;
				canonBulletPosY = underCanonPosY;
			}

		if (canonBulletShot) {
			canonBulletPosX = canonBulletPosX + canonBulletSpeed;
			if (canonBulletPosX >= 1250) {
				canonBulletPosX = 0;
				canonBulletShot = false;
			}
		}

		if (!isCanonAlive) {
			canonBulletTimer--;
			if (canonBulletTimer <= 0) {
				canonBulletShot = true;
				canonBulletTimer = 20;
			}
		}

		//　弾と敵機の当たり判定
		if (isEnemyAlive && isBulletShot) {
			bullet2enemyX = enemyPosX - bulletPosX;
			bullet2enemyY = enemyPosY - bulletPosY;
			bullet2enemy = sqrtf((bullet2enemyX * bullet2enemyX) + (bullet2enemyY * bullet2enemyY));

			if (enemyRadius + bulletRadius >= bullet2enemy) {
				isEnemyAlive = false;
				isBulletShot = false;
			}
		}

		//　敵機の弾と自機の当たり判定
		if (isPlayerAlive && enemyBulletShot) {
			enemyBullet2playerX = playerPosX - enemyBulletPosX;
			enemyBullet2playerY = playerPosY - enemyBulletPosY;
			enemyBullet2player = sqrtf((enemyBullet2playerX * enemyBullet2playerX) + (enemyBullet2playerY * enemyBullet2playerY));

			if (enemyBulletRadius + playerRadius >= enemyBullet2player) {
				isPlayerAlive = false;
				enemyBulletShot = false;
			}
		}

		//　弾と砲台の当たり判定
		if (isBulletShot) {
			bullet2canonX = leftCanonPosX - bulletPosX;
			bullet2canonY = overCanonPosY - bulletPosY;
			bullet2canon = sqrtf((bullet2canonX * bullet2canonX) + (bullet2canonY * bullet2canonY));

			if (canonRadius + bulletRadius >= bullet2canon) {
				isBulletShot = false;
			}
		}


		if (isBulletShot) {
			bullet2canonX = leftCanonPosX - bulletPosX;
			bullet2canonY = centerCanonPosY - bulletPosY;
			bullet2canon = sqrtf((bullet2canonX * bullet2canonX) + (bullet2canonY * bullet2canonY));

			if (canonRadius + bulletRadius >= bullet2canon) {
				isBulletShot = false;
			}
		}

		//　自機と敵機の当たり判定
		if (isEnemyAlive && isPlayerAlive) {
			player2enemyX = enemyPosX - playerPosX;
			player2enemyY = enemyPosY - playerPosY;
			player2enemy = sqrtf((player2enemyX * player2enemyX) + (player2enemyY * player2enemyY));

			if (enemyRadius + playerRadius >= player2enemy) {
				isPlayerAlive = false;
				isBulletShot = false;
			}
		}

		//　自機と砲台の当たり判定
		if (isPlayerAlive) {
			player2canonX = leftCanonPosX - playerPosX;
			player2canonY = overCanonPosY - playerPosY;
			player2canon = sqrtf((player2canonX * player2canonX) + (player2canonY * player2canonY));

			if (canonRadius + playerRadius >= player2canon) {
				isPlayerAlive = false;
			}
		}

		if (isPlayerAlive) {
			player2canonX = leftCanonPosX - playerPosX;
			player2canonY = centerCanonPosY - playerPosY;
			player2canon = sqrtf((player2canonX * player2canonX) + (player2canonY * player2canonY));

			if (canonRadius + playerRadius >= player2canon) {
				isPlayerAlive = false;
			}
		}

		if (isPlayerAlive) {
			player2canonX = leftCanonPosX - playerPosX;
			player2canonY = underCanonPosY - playerPosY;
			player2canon = sqrtf((player2canonX * player2canonX) + (player2canonY * player2canonY));

			if (canonRadius + playerRadius >= player2canon) {
				isPlayerAlive = false;
			}
		}

		//　自機と砲台の弾の当たり判定
		if (isPlayerAlive) {
			canonBullet2playerX = playerPosX - canonBulletPosX;
			canonBullet2playerY = playerPosY - canonBulletPosY;
			canonBullet2player = sqrtf((canonBullet2playerX * canonBullet2playerX) + (canonBullet2playerY * canonBullet2playerY));

			if (canonBulletRadius + playerRadius >= canonBullet2player) {
				isPlayerAlive = false;
				canonBulletShot = false;
			}
		}


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		if (isPlayerAlive) {
			Novice::DrawEllipse((int)playerPosX, (int)playerPosY, (int)playerRadius, (int)playerRadius, 0.0f, BLUE, kFillModeSolid);
		}

		if (isEnemyAlive) {
			Novice::DrawEllipse((int)enemyPosX, (int)enemyPosY, (int)enemyRadius, (int)enemyRadius, 0.0f, WHITE, kFillModeSolid);
		}

		if (isCanonAlive) {
			Novice::DrawEllipse((int)leftCanonPosX, (int)overCanonPosY, (int)canonRadius, (int)canonRadius, 0.0f, BLACK, kFillModeSolid);

			Novice::DrawEllipse((int)leftCanonPosX, (int)underCanonPosY, (int)canonRadius, (int)canonRadius, 0.0f, BLACK, kFillModeSolid);

			Novice::DrawEllipse((int)leftCanonPosX, (int)centerCanonPosY, (int)canonRadius, (int)canonRadius, 0.0f, BLACK, kFillModeSolid);

			Novice::DrawTriangle((int)leftCanonPosX,
				(int)overCanonPosY - (int)canonBulletRadius,

				(int)leftCanonPosX - (int)canonBulletRadius,
				(int)overCanonPosY + (int)canonBulletRadius,

				(int)leftCanonPosX + (int)canonBulletRadius,
				(int)overCanonPosY + (int)canonBulletRadius,
				0x00000000, kFillModeSolid);

			Novice::DrawTriangle((int)leftCanonPosX,
				(int)centerCanonPosY - (int)canonBulletRadius,

				(int)leftCanonPosX - (int)canonBulletRadius,
				(int)centerCanonPosY + (int)canonBulletRadius,

				(int)leftCanonPosX + (int)canonBulletRadius,
				(int)centerCanonPosY + (int)canonBulletRadius,
				0x00000000, kFillModeSolid);

			Novice::DrawTriangle((int)leftCanonPosX,
				(int)underCanonPosY - (int)canonBulletRadius,

				(int)leftCanonPosX - (int)canonBulletRadius,
				(int)underCanonPosY + (int)canonBulletRadius,

				(int)leftCanonPosX + (int)canonBulletRadius,
				(int)underCanonPosY + (int)canonBulletRadius,
				0x00000000, kFillModeSolid);
		
			Novice::DrawEllipse((int)canonBulletPosX, (int)canonBulletPosY, (int)canonBulletRadius, (int)canonBulletRadius, 0.0f, BLACK, kFillModeSolid);
		}

		if (isBulletShot) {
			Novice::DrawEllipse((int)bulletPosX, (int)bulletPosY, (int)bulletRadius, (int)bulletRadius, 0.0f, BLUE, kFillModeSolid);
		}

		if (enemyBulletShot) {
			Novice::DrawEllipse((int)enemyBulletPosX, (int)enemyBulletPosY, (int)enemyBulletRadius, (int)enemyBulletRadius, 0.0f, 0xFFFFFFFF, kFillModeSolid);
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
