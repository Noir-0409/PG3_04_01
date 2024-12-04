#include <Novice.h>
#include <Math.h>

const char kWindowTitle[] = "楽園からの追放";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };
	//変数宣言

	//自機の情報
	float playerPosX = 640.0f;
	float playerPosY = 500.0f;
	float playerRadius = 30.0f;
	float playerSpeed = 12.0f;
	int isPlayerAlive = true;
	int playerRespawnTimer = 1;
	float playerHP[1] = { 10 };
	float playertimer = 15.0f;

	//弾の情報
	float bulletPosX = 0.0f;
	float bulletPosY = 0.0f;
	float bulletSpeed = 30.0f;
	float bulletRadius = 20.0f;
	int isBulletShot = false;

	//　敵機の情報
	float enemyPosX = 640.0f;
	float enemyPosY = 120.0f;
	float enemyRadius = 65.0f;
	float enemySpeed = 8.0f;
	int isEnemyAlive = true;
	int enemyRespawnTimer = 5;
	float enemyHP[1] = { 30 };

	//　敵機の弾の情報
	float enemyBulletPosX = 0.0f;
	float enemyBulletPosY = 0.0f;
	float enemyBulletSpeed = 15.0f;
	float enemyBulletRadius = 25.0f;
	int enemyBulletShot = false;
	int enemyBulletTimer = 120;

	//　砲台の情報
	int canonPosX[4] = { 30,1250,30,1250 };
	int canonPosY[4] = { 400,550,690,250 };
	float canonRadius = 30.0f;
	int isCanonAlive = true;

	//　砲台の弾の情報
	int canonBulletPosX[4] = { 0 };
	int canonBulletPosY[4] = { 0 };
	float canonBulletSpeed = 8.0f;
	float canonBulletRadius = 15.0f;
	int canonBulletShot[4] = {false,false,false,false};

	//　背景の情報
	float backGraundY = 0.0f;
	int backMove = true;

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

	//　リソース画像
	int playerGH = Novice::LoadTexture("./resources/player_export.png");
	int playerGH2 = Novice::LoadTexture("./resources/player2-export.png");
	int enemyGH = Novice::LoadTexture("./resources/enemy2.png");
	int canonGH = Novice::LoadTexture("./resources/canon-export.png");
	int bulletGH = Novice::LoadTexture("./resources/bullet.png");
	int enemyBulletGH = Novice::LoadTexture("./resources/enemybullet.png");
	int canonBulletGH = Novice::LoadTexture("./resources/canonbullet.png");
	int backagraund = Novice::LoadTexture("./resources/backgraund-export.png");
	int titleGH = Novice::LoadTexture("./resources/title.png");
	int clearGH = Novice::LoadTexture("./resources/clear.png");
	int overGH = Novice::LoadTexture("./resources/over.png");

	int titleBGM = Novice::LoadAudio("./BGM/titleBGM.wav");
	int playBGM = Novice::LoadAudio("./BGM/playBGM.wav");
	

	//　シーン画面
	enum SCENE {
		title=0,
		play,
		clear,
		over
	};
	
	int sceneNum = title;
	 


	

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
		
		switch (sceneNum) {
		case title:
			if (keys[DIK_RETURN]&&preKeys[DIK_RETURN]==false) {

				playerHP[0] = 10;
				enemyHP[0] = 30;
				sceneNum = play;
				playerPosX = 640;
				playerPosY = 500;
				isBulletShot = false;
				enemyPosX = 640;
				enemyPosY = 120;
				enemyBulletShot = false;
				canonBulletShot[0] =  false;
			}
			break;

		case play:
			
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

			// 自機のアニメーション
			if (isPlayerAlive) {
				playertimer--;
				if (playertimer <= 0) {
					playertimer = 20.0f;
				}

			}

			//　左上の弾の発射処理
			if (canonBulletShot[0] == false)
				if (isCanonAlive == 1) {
					canonBulletShot[0] = true;
					canonBulletPosX[0] = canonPosX[0];
					canonBulletPosY[0] = canonPosY[0];
				}

			if (canonBulletShot[0]) {
				canonBulletPosX[0] = canonBulletPosX[0] + (int)canonBulletSpeed;
				if (canonBulletPosX[0] >= 1500) {
					canonBulletPosX[0] = canonPosX[0];
					canonBulletShot[0] = false;
				}
			}


			//　右中の弾の発射処理
			if (canonBulletShot[1] == false)
				if (isCanonAlive == 1) {
					canonBulletShot[1] = true;
					canonBulletPosX[1] = canonPosX[1];
					canonBulletPosY[1] = canonPosY[1];
				}

			if (canonBulletShot[1]) {
				canonBulletPosX[1] = canonBulletPosX[1] - (int)canonBulletSpeed;
				if (canonBulletPosX[1] <= 0) {
					canonBulletPosX[1] = canonPosX[1];
					canonBulletShot[1] = false;
				}
			}



			//　左下の弾の発射処理
			if (canonBulletShot[2] == false)
				if (isCanonAlive == 1) {
					canonBulletShot[2] = true;
					canonBulletPosX[2] = canonPosX[2];
					canonBulletPosY[2] = canonPosY[2];
				}

			if (canonBulletShot[2]) {
				canonBulletPosX[2] = canonBulletPosX[2] + (int)canonBulletSpeed;
				if (canonBulletPosX[2] >= 1700) {
					canonBulletPosX[2] = canonPosX[2];
					canonBulletShot[2] = false;
				}
			}

			//　右上の弾の発射処理
			if (canonBulletShot[3] == false)
				if (isCanonAlive == 1) {
					canonBulletShot[3] = true;
					canonBulletPosX[3] = canonPosX[3];
					canonBulletPosY[3] = canonPosY[3];
				}

			if (canonBulletShot[3]) {
				canonBulletPosX[3] = canonBulletPosX[3] - (int)canonBulletSpeed;
				if (canonBulletPosX[3] <= -200) {
					canonBulletPosX[3] = canonPosX[3];
					canonBulletShot[3] = false;
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
					enemyHP[0] -= 1;
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
					playerHP[0] -= 1;
				}
			}

			//　弾と砲台の当たり判定
			if (isBulletShot) {
				bullet2canonX = canonPosX[0] - bulletPosX;
				bullet2canonY = canonPosY[0] - bulletPosY;
				bullet2canon = sqrtf((bullet2canonX * bullet2canonX) + (bullet2canonY * bullet2canonY));

				if (canonRadius + bulletRadius >= bullet2canon) {
					isBulletShot = false;
				}
			}


			if (isBulletShot) {
				bullet2canonX = canonPosX[1] - bulletPosX;
				bullet2canonY = canonPosY[1] - bulletPosY;
				bullet2canon = sqrtf((bullet2canonX * bullet2canonX) + (bullet2canonY * bullet2canonY));

				if (canonRadius + bulletRadius >= bullet2canon) {
					isBulletShot = false;
				}
			}

			if (isBulletShot) {
				bullet2canonX = canonPosX[2] - bulletPosX;
				bullet2canonY = canonPosY[2] - bulletPosY;
				bullet2canon = sqrtf((bullet2canonX * bullet2canonX) + (bullet2canonY * bullet2canonY));

				if (canonRadius + bulletRadius >= bullet2canon) {
					isBulletShot = false;
				}
			}

			if (isBulletShot) {
				bullet2canonX = canonPosX[3] - bulletPosX;
				bullet2canonY = canonPosY[3] - bulletPosY;
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
					playerHP[0] -= 1;
				}
			}

			//　自機と砲台の当たり判定
			if (isPlayerAlive) {
				player2canonX = canonPosX[0] - playerPosX;
				player2canonY = canonPosY[0] - playerPosY;
				player2canon = sqrtf((player2canonX * player2canonX) + (player2canonY * player2canonY));

				if (canonRadius + playerRadius >= player2canon) {
					isPlayerAlive = false;
					playerHP[0] -= 1;
				}
			}


			if (isPlayerAlive) {
				player2canonX = canonPosX[1] - playerPosX;
				player2canonY = canonPosY[1] - playerPosY;
				player2canon = sqrtf((player2canonX * player2canonX) + (player2canonY * player2canonY));

				if (canonRadius + playerRadius >= player2canon) {
					isPlayerAlive = false;
					playerHP[0] -= 1;
				}
			}

			if (isPlayerAlive) {
				player2canonX = canonPosX[2] - playerPosX;
				player2canonY = canonPosY[2] - playerPosY;
				player2canon = sqrtf((player2canonX * player2canonX) + (player2canonY * player2canonY));

				if (canonRadius + playerRadius >= player2canon) {
					isPlayerAlive = false;
					playerHP[0] -= 1;
				}
			}

			if (isPlayerAlive) {
				player2canonX = canonPosX[3] - playerPosX;
				player2canonY = canonPosY[3] - playerPosY;
				player2canon = sqrtf((player2canonX * player2canonX) + (player2canonY * player2canonY));

				if (canonRadius + playerRadius >= player2canon) {
					isPlayerAlive = false;
					playerHP[0] -= 1;
				}
			}
			//　自機と砲台の弾の当たり判定
			if (isPlayerAlive) {
				canonBullet2playerX = playerPosX - canonBulletPosX[0];
				canonBullet2playerY = playerPosY - canonBulletPosY[0];
				canonBullet2player = sqrtf((canonBullet2playerX * canonBullet2playerX) + (canonBullet2playerY * canonBullet2playerY));

				if (canonBulletRadius + playerRadius >= canonBullet2player) {
					isPlayerAlive = false;
					canonBulletShot[0] = false;
					playerHP[0] -= 1;
				}
			}

			if (isPlayerAlive) {
				canonBullet2playerX = playerPosX - canonBulletPosX[1];
				canonBullet2playerY = playerPosY - canonBulletPosY[1];
				canonBullet2player = sqrtf((canonBullet2playerX * canonBullet2playerX) + (canonBullet2playerY * canonBullet2playerY));

				if (canonBulletRadius + playerRadius >= canonBullet2player) {
					isPlayerAlive = false;
					canonBulletShot[1] = false;
					playerHP[0] -= 1;
				}
			}

			if (isPlayerAlive) {
				canonBullet2playerX = playerPosX - canonBulletPosX[2];
				canonBullet2playerY = playerPosY - canonBulletPosY[2];
				canonBullet2player = sqrtf((canonBullet2playerX * canonBullet2playerX) + (canonBullet2playerY * canonBullet2playerY));

				if (canonBulletRadius + playerRadius >= canonBullet2player) {
					isPlayerAlive = false;
					canonBulletShot[2] = false;
					playerHP[0] -= 1;
				}
			}

			if (isPlayerAlive) {
				canonBullet2playerX = playerPosX - canonBulletPosX[3];
				canonBullet2playerY = playerPosY - canonBulletPosY[3];
				canonBullet2player = sqrtf((canonBullet2playerX * canonBullet2playerX) + (canonBullet2playerY * canonBullet2playerY));

				if (canonBulletRadius + playerRadius >= canonBullet2player) {
					isPlayerAlive = false;
					canonBulletShot[3] = false;
					playerHP[0] -= 1;
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
					playerRespawnTimer = 15;
				}
			}

			//　敵機のリスポーン処理
			if (!isEnemyAlive) {
				enemyRespawnTimer--;
				if (enemyRespawnTimer <= 0) {
					isEnemyAlive = true;
					enemyRespawnTimer = 3;
				}
			}




			//　背景の移動
			if (backMove) {
				backGraundY = backGraundY + 2;

				if (backGraundY >= 720) {
					backGraundY = 0;
				}
			}
			if (enemyHP[0] == 0) {
				sceneNum = clear;
			}

			if (playerHP[0] == 0) {
				sceneNum = over;
			}

			break;

		case clear:


			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {
				
				sceneNum = title;
			}
			break;

		case over:
			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {
				sceneNum = title;
			}
			break;
		}

		
	

		


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		/// 

		switch (sceneNum) {
		case title:
			Novice::DrawSprite(0, 0, titleGH, 1.0f, 1.0f, 0.0f, WHITE);
			Novice::PlayAudio(titleBGM, true, 0.7f);
			Novice::StopAudio(titleBGM);
			break;


		case play:

			Novice::DrawSprite(0, (int)backGraundY, backagraund, 1.0f, 1.0f, 0.0f, WHITE);

			Novice::DrawSprite(0, (int)backGraundY - 720, backagraund, 1.0f, 1.0f, 0.0f, WHITE);

			if (isPlayerAlive) {
				if (playertimer >= 10) {
					Novice::DrawSprite((int)playerPosX - (int)playerRadius - 20, (int)playerPosY - (int)playerRadius, playerGH, 1.0f, 1.0f, 0.0f, WHITE);
				} else if (playertimer <= 10) {
					Novice::DrawSprite((int)playerPosX - (int)playerRadius - 20, (int)playerPosY - (int)playerRadius, playerGH2, 1.0f, 1.0f, 0.0f, WHITE);
				}
			}


			if (isBulletShot) {
				Novice::DrawTriangle((int)bulletPosX,
					(int)bulletPosY - (int)bulletRadius,

					(int)bulletPosX - (int)bulletRadius,
					(int)bulletPosY + (int)bulletRadius,

					(int)bulletPosX + (int)bulletRadius,
					(int)bulletPosY + (int)bulletRadius,
					0x00000000, kFillModeSolid);
			}

			if (enemyBulletShot) {
				Novice::DrawTriangle((int)enemyBulletPosX,
					(int)enemyBulletPosY - (int)enemyBulletRadius,

					(int)enemyBulletPosX - (int)enemyBulletRadius,
					(int)enemyBulletPosY + (int)enemyBulletRadius,

					(int)enemyBulletPosX + (int)enemyBulletRadius,
					(int)enemyBulletPosY + (int)enemyBulletRadius,
					0x00000000, kFillModeSolid);
			}

			if (isBulletShot) {
				Novice::DrawSprite((int)bulletPosX - (int)bulletRadius, (int)bulletPosY - (int)bulletRadius, bulletGH, 1.2f, 1.2f, 0.0f, WHITE);
			}

			if (enemyBulletShot) {
				Novice::DrawSprite((int)enemyBulletPosX - (int)enemyBulletRadius, (int)enemyBulletPosY - (int)enemyBulletRadius, enemyBulletGH, 1.2f, 1.2f, 0.0f, 0xFFFFFFFF);
			}

			if (isEnemyAlive) {
				Novice::DrawSprite((int)enemyPosX - (int)enemyRadius - 40, (int)enemyPosY - (int)enemyRadius, enemyGH, 0.8f, 0.8f, 0.0f, 0xFFFFFFFF);
			}

			if (isCanonAlive) {
				Novice::DrawSprite((int)canonPosX[0] - (int)canonRadius, (int)canonPosY[0] - (int)canonRadius - 20, canonGH, 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite((int)canonPosX[1] - (int)canonRadius - 60, (int)canonPosY[1] - (int)canonRadius - 20, canonGH, 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite((int)canonPosX[2] - (int)canonRadius, (int)canonPosY[2] - (int)canonRadius - 40, canonGH, 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite((int)canonPosX[3] - (int)canonRadius - 60, (int)canonPosY[3] - (int)canonRadius - 20, canonGH, 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawTriangle((int)canonPosX[0],
					(int)canonPosY[0] - (int)canonBulletRadius,

					(int)canonPosX[0] - (int)canonBulletRadius,
					(int)canonPosY[0] + (int)canonBulletRadius,

					(int)canonPosX[0] + (int)canonBulletRadius,
					(int)canonPosY[0] + (int)canonBulletRadius,
					0x00000000, kFillModeSolid);

				Novice::DrawSprite((int)canonBulletPosX[0] - (int)canonBulletRadius, (int)canonBulletPosY[0] - (int)canonBulletRadius, canonBulletGH, 1.2f, 1.2f, 0.0f, WHITE);



				Novice::DrawTriangle((int)canonPosX[1],
					(int)canonPosY[1] - (int)canonBulletRadius,

					(int)canonPosX[1] - (int)canonBulletRadius,
					(int)canonPosY[1] + (int)canonBulletRadius,

					(int)canonPosX[1] + (int)canonBulletRadius,
					(int)canonPosY[1] + (int)canonBulletRadius,
					0x00000000, kFillModeSolid);

				Novice::DrawSprite((int)canonBulletPosX[1] - (int)canonBulletRadius, (int)canonBulletPosY[1] - (int)canonBulletRadius, canonBulletGH, 1.2f, 1.2f, 0.0f, WHITE);


				Novice::DrawTriangle((int)canonPosX[2],
					(int)canonPosY[2] - (int)canonBulletRadius,

					(int)canonPosX[2] - (int)canonBulletRadius,
					(int)canonPosY[2] + (int)canonBulletRadius,

					(int)canonPosX[2] + (int)canonBulletRadius,
					(int)canonPosY[2] + (int)canonBulletRadius,
					0x00000000, kFillModeSolid);

				Novice::DrawSprite((int)canonBulletPosX[2] - (int)canonBulletRadius, (int)canonBulletPosY[2] - (int)canonBulletRadius, canonBulletGH, 1.2f, 1.2f, 0.0f, WHITE);

				Novice::DrawTriangle((int)canonPosX[3],
					(int)canonPosY[3] - (int)canonBulletRadius,

					(int)canonPosX[3] - (int)canonBulletRadius,
					(int)canonPosY[3] + (int)canonBulletRadius,

					(int)canonPosX[3] + (int)canonBulletRadius,
					(int)canonPosY[3] + (int)canonBulletRadius,
					0x00000000, kFillModeSolid);

				Novice::DrawSprite((int)canonBulletPosX[3] - (int)canonBulletRadius, (int)canonBulletPosY[3] - (int)canonBulletRadius, canonBulletGH, 1.2f, 1.2f, 0.0f, WHITE);
			}





			Novice::PlayAudio(playBGM, true, 0.7f);
			Novice::StopAudio(playBGM);
			break;

		case clear:
			Novice::DrawSprite(0, 0, clearGH, 1.0f, 1.0f, 0.0f, WHITE);
			break;

		case over:
			Novice::DrawSprite(0, 0, overGH, 1.0f, 1.0f, 0.0f, WHITE);
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
