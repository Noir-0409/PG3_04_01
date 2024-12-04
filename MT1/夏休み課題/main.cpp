#include <Novice.h>
#include <Math.h>
#include <Vector2.h>

const char kWindowTitle[] = "夏休み課題";

//　変数宣言

//　自機の情報
float playerPosX = 150.0f;
float playerPosY = 540.0f;
float playerSpeed = 3.0f;
float playerWidth = 40.0f;
float playerHeight = 40.0f;
float playerTimer = 0.0f;
int playerMove = false;

//　敵機の情報
float enemyPosX = 1810.0f;
float enemyPosY = 540.0f;
float enemyWidth = 40.0f;
float enemyHeight = 40.0f;

//　障害物の情報
float obj1PosX[5] = {500,500,980,1460,1460};
float obj1PosY[5] = { 180,900,540,180,900 };
float obj1Width[5] = { 50,50,150,50,50 };
float obj1Height[5] = { 200,200,150,200,200 };

float obj2PosX[9] = { 525,675,300,775,1125,1275,1200,1625,1600 };
float obj2PosY[9] = { 300,125,800,600,300,450,925,250,725 };
float obj2Width[9] = { 50,200,50,50,50,200,200,50,200 };
float obj2Height[9] = { 200,50,200,200,200,50,50,200,50 };

float obj3PosX[9] = { 325,580,580,875,1130,1130,1425,1680,1680 };
float obj3PosY[9] = { 540,220,830,540,220,830,540,220,830 };
float obj3Width[9] = { 50,50,50,50,50,50,50,50,50 };
float obj3Height[9] = { 200,200,200,200,200,200,200,200,200 };

//　当たり判定を管理する変数
float playerLeftPosX = 0.0f;
float playerRightPosX = 0.0f;
float playerTopPosY = 0.0f;
float playerBottomPosY = 0.0f;

float enemyLeftPosX = 0.0f;
float enemyRightPosX = 0.0f;
float enemyTopPosY = 0.0f;
float enemyBottomPosY = 0.0f;

float obj1LeftPosX[5] = { 0.0f };
float obj1RightPosX[5] = { 0.0f };
float obj1TopPosY[5] = { 0.0f };
float obj1BottomPosY[5] = { 0.0f };

float obj2LeftPosX[9] = { 0.0f };
float obj2RightPosX[9] = { 0.0f };
float obj2TopPosY[9] = { 0.0f };
float obj2BottomPosY[9] = { 0.0f };

float obj3LeftPosX[9] = { 0.0f };
float obj3RightPosX[9] = { 0.0f };
float obj3TopPosY[9] = { 0.0f };
float obj3BottomPosY[9] = { 0.0f };

//　敵の振り向きを管理する変数
float enemyTurnTimer = 300.0f;
float enemyStopTimer = 180.0f;

//　敵に当たっているかどうかを管理する変数
int isHitEnemy = false;
int isHitX = false;
int isHitY = false;

// 残り時間を管理する変数
float countTimer = 1800.0f;

//　始まりのカウントを管理する変数
float redyCount = 240.0f;

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1960, 1080);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	
	//　リソース画像
	int playerFrontGH[3] = { Novice::LoadTexture("./Resources/playerFront1.png"),

	Novice::LoadTexture("./Resources/playerFront2.png"),

	Novice::LoadTexture("./Resources/playerFront3.png") };

	int playerBackGH[3] = { Novice::LoadTexture("./Resources/playerBack1.png"),

	Novice::LoadTexture("./Resources/playerBack2.png"),

	Novice::LoadTexture("./Resources/playerBack3.png") };

	int playerLeftGH[3] = { Novice::LoadTexture("./Resources/playerLeft1.png"),

	Novice::LoadTexture("./Resources/playerLeft2.png"),

	Novice::LoadTexture("./Resources/playerLeft3.png") };

	int playerRightGH[3] = { Novice::LoadTexture("./Resources/playerRight1.png"),

	Novice::LoadTexture("./Resources/playerRight2.png"),

	Novice::LoadTexture("./Resources/playerRight3.png") };

	int enemyGH[2]={Novice::LoadTexture("./Resources/enemyLeft.png"),
	
	Novice::LoadTexture("./Resources/enemyRight.png")};

	int selectStage1GH = Novice::LoadTexture("./Resources/selectstage1.png");

	int selectStage2GH = Novice::LoadTexture("./Resources/selectstage2.png");
	
	int selectStage3GH = Novice::LoadTexture("./Resources/selectstage3.png");
	
	int stage1GH = Novice::LoadTexture("./Resources/stage1BG.png");
	
	int objStage1 = Novice::LoadTexture("./Resources/obj1.png");
	
	int centerObjStage1 = Novice::LoadTexture("./Resources/obj1[2].png");

	int objStage2H = Novice::LoadTexture("./Resources/obj2h.png");

	int objStage2W = Novice::LoadTexture("./Resources/obj22.png");

	int obj3GH = Novice::LoadTexture("./Resources/obj3.png");
	
	int timerGH = Novice::LoadTexture("./Resources/timer.png");
	
	int redyNumberGH[3] = { Novice::LoadTexture("./Resources/redy1.png"),
	
		Novice::LoadTexture("./Resources/redy2.png"),
	
		Novice::LoadTexture("./Resources/redy3.png") };

	int redyStartGH = Novice::LoadTexture("./Resources/redyStart.png");
	
	int numberGH[10] = { Novice::LoadTexture("./Resources/0.png"),
	
		Novice::LoadTexture("./Resources/1.png"),
	
		Novice::LoadTexture("./Resources/2.png"),
	
		Novice::LoadTexture("./Resources/3.png"),
	
		Novice::LoadTexture("./Resources/4.png"),
	
		Novice::LoadTexture("./Resources/5.png"),
	
		Novice::LoadTexture("./Resources/6.png"),
	
		Novice::LoadTexture("./Resources/7.png"),
	
		Novice::LoadTexture("./Resources/8.png"),
	
		Novice::LoadTexture("./Resources/9.png") };

	int titleGH = Novice::LoadTexture("./Resources/title2.png");

	int stopGH = Novice::LoadTexture("./Resources/stop.png");

	int clear1GH = Novice::LoadTexture("./Resources/clear1.png");

	int clear2GH = Novice::LoadTexture("./Resources/clear2.png");

	int over1GH = Novice::LoadTexture("./Resources/over1.png");

	int over2GH = Novice::LoadTexture("./Resources/over2.png");

	//　BGM
	int titleBGM = Novice::LoadAudio("./BGMs/maou_bgm_fantasy08.MP3");

	int stageBGM = Novice::LoadAudio("./BGMs/maou_bgm_fantasy10.MP3");
	// シーン画面
	enum SCENE {
		title=0,
		stageSelect1,
		stageSelect2,
		stageSelect3,
		redyStage1,
		redyStage2,
		redyStage3,
		stage1,
		stage2,
		stage3,
		clear11,
		clear21,
		clear12,
		clear22,
		clear13,
		clear23,
		over11,
		over21,
		over12,
		over22,
		over13,
		over23
	};

	enum PLAYER_DERICTION {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	int sceneNum = title;

	//　プレイヤーの向きを管理する変数
	int playerDirection = RIGHT;
	//　タイトル画面の変化を管理する変数
	float titleTimer = 0.0f;

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

		playerLeftPosX = playerPosX - playerWidth;
		playerRightPosX = playerPosX + playerWidth;
		playerTopPosY = playerPosY - playerHeight;
		playerBottomPosY = playerPosY + playerHeight;

		enemyLeftPosX = enemyPosX - enemyWidth;
		enemyRightPosX = enemyPosX + enemyWidth;
		enemyTopPosY = enemyPosY - enemyHeight;
		enemyBottomPosY = enemyPosY + enemyHeight;

		for (int i = 0; i < 5; i++) {

			obj1LeftPosX[i] = obj1PosX[i] - obj1Width[i];
			obj1RightPosX[i] = obj1PosX[i] + obj1Width[i];
			obj1TopPosY[i] = obj1PosY[i] - obj1Height[i];
			obj1BottomPosY[i] = obj1PosY[i] + obj1Height[i];

		}

		for (int j = 0; j < 9; j++) {

			obj2LeftPosX[j] = obj2PosX[j] - obj2Width[j];
			obj2RightPosX[j] = obj2PosX[j] + obj2Width[j];
			obj2TopPosY[j] = obj2PosY[j] - obj2Height[j];
			obj2BottomPosY[j] = obj2PosY[j] + obj2Height[j];

		}

		for (int i = 0; i < 9; i++) {

			obj3LeftPosX[i] = obj3PosX[i] - obj3Width[i];
			obj3RightPosX[i] = obj3PosX[i] + obj3Width[i];
			obj3TopPosY[i] = obj3PosY[i] - obj3Height[i];
			obj3BottomPosY[i] = obj3PosY[i] + obj3Height[i];
			
		}

		playerTimer++;

		if (playerTimer > 60) {

			playerTimer = 0;

		}

		titleTimer++;

		if (titleTimer > 60) {

			titleTimer = 0;

		}
		

		//　シーン切り替え処理
		switch (sceneNum) {

		case title:

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

				playerPosX = 150.0f;
				playerPosY = 540.0f;
				enemyTurnTimer = 300.0f;
				enemyStopTimer = 180.0f;
				countTimer = 1800.0f;
				redyCount = 240.0f;

			}

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

				sceneNum = stageSelect1;

			}
			break;

		case stageSelect1:

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

				sceneNum = redyStage1;

				Novice::StopAudio(titleBGM);

			}

			if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false ||
				keys[DIK_D] && preKeys[DIK_D] == false) {

				sceneNum = stageSelect2;

			}

			if (keys[DIK_LEFT] && preKeys[DIK_LEFT] == false ||
				keys[DIK_A] && preKeys[DIK_A] == false) {

				sceneNum = stageSelect3;

			}
			break;

		case stageSelect2:

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

				sceneNum = redyStage2;

				Novice::StopAudio(titleBGM);

			}

			if (keys[DIK_LEFT] && preKeys[DIK_LEFT] == false ||
				keys[DIK_A] && preKeys[DIK_A] == false) {

				sceneNum = stageSelect1;

			}

			if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false ||
				keys[DIK_D] && preKeys[DIK_D] == false) {

				sceneNum = stageSelect3;

			}
			break;

		case stageSelect3:

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

				sceneNum = redyStage3;

				Novice::StopAudio(titleBGM);

			}

			if (keys[DIK_LEFT] && preKeys[DIK_LEFT] == false ||
				keys[DIK_A] && preKeys[DIK_A] == false) {

				sceneNum = stageSelect2;

			}

			if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false ||
				keys[DIK_D] && preKeys[DIK_D] == false) {

				sceneNum = stageSelect1;
			}
			break;

		case redyStage1:

			redyCount--;

			if (redyCount == 0) {

				sceneNum = stage1;

			}

			break;

		case redyStage2:

			redyCount--;

			if (redyCount == 0) {

				sceneNum = stage2;

			}

			break;

		case redyStage3:

			redyCount--;

			if (redyCount == 0) {

				sceneNum = stage3;

			}

			break;

		case stage1:

			//　自機の移動処理
			if (keys[DIK_W] || keys[DIK_UP]) {

				playerPosY -= playerSpeed;
				playerDirection = UP;

			}

			if (keys[DIK_S] || keys[DIK_DOWN]) {

				playerPosY += playerSpeed;
				playerDirection = DOWN;

			}

			if (keys[DIK_A] || keys[DIK_LEFT]) {

				playerPosX -= playerSpeed;
				playerDirection = LEFT;

			}

			if (keys[DIK_D] || keys[DIK_RIGHT]) {

				playerPosX += playerSpeed;
				playerDirection = RIGHT;

			}

			if (keys[DIK_W] && preKeys[DIK_W] || keys[DIK_UP] && preKeys[DIK_UP] ||
				keys[DIK_S] && preKeys[DIK_S] || keys[DIK_DOWN] && preKeys[DIK_DOWN] ||
				keys[DIK_A] && preKeys[DIK_A] || keys[DIK_LEFT] && preKeys[DIK_LEFT] ||
				keys[DIK_D] && preKeys[DIK_D] || keys[DIK_RIGHT] && preKeys[DIK_RIGHT]) {

				playerMove = true;

			} else {

				playerMove = false;

			}

			//　自機が画面外に出ない様にする処理
			if (playerPosX - playerWidth <= 0) {

				playerPosX += playerSpeed;

			}

			if (playerPosX + playerWidth >= 1960) {

				playerPosX -= playerSpeed;

			}

			if (playerPosY - playerHeight <= 0) {

				playerPosY += playerSpeed;

			}

			if (playerPosY + playerHeight >= 1080) {

				playerPosY -= playerSpeed;

			}

			//　自機と敵機の当たり判定
			if (enemyLeftPosX < playerRightPosX && playerLeftPosX < enemyRightPosX) {

				isHitX = true;

			} else {

				isHitX = false;

			}

			if (enemyTopPosY < playerBottomPosY && playerTopPosY < enemyBottomPosY) {

				isHitY = true;

			} else {

				isHitY = false;

			}

			if (isHitX && isHitY) {

				isHitEnemy = true;

			} else {

				isHitEnemy = false;

			}

			//　自機と障害物の当たり判定

			//　ステージ１のX座標
			if (obj1LeftPosX[0] < playerRightPosX) {

				if (obj1RightPosX[0] > playerRightPosX) {

					if (obj1BottomPosY[0] > playerTopPosY || obj1TopPosY[1] < playerBottomPosY) {

						playerPosX -= playerSpeed;

					}
				}
			}

			if (obj1RightPosX[0] > playerLeftPosX) {

				if (obj1LeftPosX[0] < playerLeftPosX) {

					if (obj1BottomPosY[0] > playerTopPosY || obj1TopPosY[1] < playerBottomPosY) {

						playerPosX += playerSpeed;

					}
				}
			}

			if (obj1LeftPosX[2] < playerRightPosX) {

				if (obj1RightPosX[2] > playerRightPosX) {

					if (obj1TopPosY[2] < playerBottomPosY && obj1BottomPosY[2] > playerTopPosY) {

						playerPosX -= playerSpeed;

					}
				}
			}

			if (obj1RightPosX[2] > playerLeftPosX) {

				if (obj1LeftPosX[2] < playerLeftPosX) {

					if (obj1TopPosY[2] < playerBottomPosY && obj1BottomPosY[2] > playerTopPosY) {

						playerPosX += playerSpeed;

					}
				}
			}

			if (obj1LeftPosX[3] < playerRightPosX) {

				if (obj1RightPosX[3] > playerRightPosX) {

					if (obj1BottomPosY[3] > playerTopPosY || obj1TopPosY[4] < playerBottomPosY) {

						playerPosX -= playerSpeed;

					}
				}
			}

			if (obj1RightPosX[3] > playerLeftPosX) {

				if (obj1LeftPosX[3] < playerLeftPosX) {

					if (obj1BottomPosY[3] > playerTopPosY || obj1TopPosY[4] < playerBottomPosY) {

						playerPosX += playerSpeed;

					}
				}
			}

			//　ステージ１のY座標
			if (obj1LeftPosX[0] < playerRightPosX - 5) {

				if (obj1RightPosX[0] > playerLeftPosX + 5) {

					if (obj1BottomPosY[0] + 5 > playerTopPosY) {

						playerPosY += playerSpeed;

					}
				}
			}

			if (obj1LeftPosX[1] < playerRightPosX - 5) {

				if (obj1RightPosX[1] > playerLeftPosX + 5) {

					if (obj1TopPosY[1] - 5 < playerBottomPosY) {

						playerPosY -= playerSpeed;

					}
				}
			}

			if (obj1LeftPosX[2] < playerRightPosX - 5) {

				if (obj1RightPosX[2] > playerLeftPosX + 7) {

					if (obj1PosY[2] > playerPosY) {

						if (obj1TopPosY[2] - 5 < playerBottomPosY) {

							playerPosY -= playerSpeed;

						}
					}
				}
			}

			if (obj1LeftPosX[2] < playerRightPosX - 5) {

				if (obj1RightPosX[2] > playerLeftPosX + 7) {

					if (obj1PosY[2] < playerPosY) {

						if (obj1BottomPosY[2] + 5 > playerTopPosY) {

							playerPosY += playerSpeed;

						}
					}
				}
			}

			if (obj1LeftPosX[3] < playerRightPosX - 5) {

				if (obj1RightPosX[3] > playerLeftPosX + 5) {

					if (obj1BottomPosY[3] + 5 > playerTopPosY) {

						playerPosY += playerSpeed;

					}
				}
			}

			if (obj1LeftPosX[4] < playerRightPosX - 5) {

				if (obj1RightPosX[4] > playerLeftPosX + 5) {

					if (obj1TopPosY[4] - 5 < playerBottomPosY) {

						playerPosY -= playerSpeed;

					}
				}
			}

			//　敵が振り向く処理
			if (enemyTurnTimer > 0) {

				enemyTurnTimer--;
			}

			if (enemyTurnTimer == 0) {

				enemyStopTimer--;
			}

			if (enemyStopTimer == 0) {

				enemyTurnTimer = 300;

				enemyStopTimer = 180;

			}

			//　時間を減らしていく処理
			if (countTimer > 0) {

				countTimer--;

			}

			//　クリア、オーバー画面に移る処理
			if (isHitEnemy) {

				sceneNum = clear11;
			}

			if (enemyTurnTimer == 0) {

				if (playerMove) {

					sceneNum = over11;
				}
			}

			if (countTimer == 0) {

				sceneNum = over11;

			}
			break;

		case stage2:

			//　自機の移動処理
			if (keys[DIK_W] || keys[DIK_UP]) {

				playerPosY -= playerSpeed;
				playerDirection = UP;

			}

			if (keys[DIK_S] || keys[DIK_DOWN]) {

				playerPosY += playerSpeed;
				playerDirection = DOWN;

			}

			if (keys[DIK_A] || keys[DIK_LEFT]) {

				playerPosX -= playerSpeed;
				playerDirection = LEFT ;

			}

			if (keys[DIK_D] || keys[DIK_RIGHT]) {

				playerPosX += playerSpeed;
				playerDirection = RIGHT ;


			}

			if (keys[DIK_W] && preKeys[DIK_W] || keys[DIK_UP] && preKeys[DIK_UP] ||
				keys[DIK_S] && preKeys[DIK_S] || keys[DIK_DOWN] && preKeys[DIK_DOWN] ||
				keys[DIK_A] && preKeys[DIK_A] || keys[DIK_LEFT] && preKeys[DIK_LEFT] ||
				keys[DIK_D] && preKeys[DIK_D] || keys[DIK_RIGHT] && preKeys[DIK_RIGHT]) {

				playerMove = true;

			} else {

				playerMove = false;

			}

			//　自機が画面外に出ない様にする処理
			if (playerPosX - playerWidth <= 0) {

				playerPosX += playerSpeed;

			}

			if (playerPosX + playerWidth >= 1960) {

				playerPosX -= playerSpeed;

			}

			if (playerPosY - playerHeight <= 0) {

				playerPosY += playerSpeed;

			}

			if (playerPosY + playerHeight >= 1080) {

				playerPosY -= playerSpeed;

			}

			//　自機と敵機の当たり判定
			if (enemyLeftPosX < playerRightPosX && playerLeftPosX < enemyRightPosX) {

				isHitX = true;

			} else {

				isHitX = false;

			}

			if (enemyTopPosY < playerBottomPosY && playerTopPosY < enemyBottomPosY) {

				isHitY = true;

			} else {

				isHitY = false;

			}

			if (isHitX && isHitY) {

				isHitEnemy = true;

			} else {

				isHitEnemy = false;

			}

			//　自機と障害物の当たり判定

			//　ステージ2のX座標
			for (int z = 0; z < 9; z++) {
				if (playerRightPosX > obj2LeftPosX[z]) {

					if (playerRightPosX < obj2RightPosX[z]) {

						if (playerBottomPosY > obj2TopPosY[z] && playerTopPosY < obj2BottomPosY[z]) {

							playerPosX -= playerSpeed;

						}
					}
				}

				if (playerLeftPosX < obj2RightPosX[z]) {

					if (playerLeftPosX > obj2LeftPosX[z]) {

						if (playerBottomPosY > obj2TopPosY[z] && playerTopPosY < obj2BottomPosY[z]) {

							playerPosX += playerSpeed;

						}
					}
				}
			}

			//　ステージ2のY座標
			for (int m = 0; m < 9; m++) {

				if (obj2LeftPosX[m] < playerRightPosX - 5) {

					if (obj2RightPosX[m] > playerLeftPosX + 5) {

						if (playerTopPosY < obj2TopPosY[m]){

							if (obj2TopPosY[m] - 5 < playerBottomPosY) {

								playerPosY -= playerSpeed;

							}
					}
				}
			}

				if (obj2LeftPosX[m] < playerRightPosX - 5) {

					if (obj2RightPosX[m] > playerLeftPosX + 5) {

						if (playerBottomPosY > obj2BottomPosY[m]) {

							if (obj2BottomPosY[m] + 5 > playerTopPosY) {

								playerPosY += playerSpeed;

							}
						}
					}
				}
			}

			//　敵が振り向く処理
			if (enemyTurnTimer > 0) {

				enemyTurnTimer--;
			}

			if (enemyTurnTimer == 0) {

				enemyStopTimer--;
			}

			if (enemyStopTimer == 0) {

				enemyTurnTimer = 300;

				enemyStopTimer = 180;

			}

			//　時間を減らしていく処理
			if (countTimer > 0) {

				countTimer--;

			}

				//　クリア、オーバー画面に移る処理
				if (isHitEnemy) {

					sceneNum = clear12;
				}

				if (enemyTurnTimer == 0) {

					if (playerMove) {

						sceneNum = over12;
					}
				}

				if (countTimer == 0) {

					sceneNum = over12;

				}
				break;

				case stage3:

					//　自機の移動処理
					if (keys[DIK_W] || keys[DIK_UP]) {

						playerPosY -= playerSpeed;
						playerDirection = UP ;


					}

					if (keys[DIK_S] || keys[DIK_DOWN]) {

						playerPosY += playerSpeed;
						playerDirection =DOWN ;


					}

					if (keys[DIK_A] || keys[DIK_LEFT]) {

						playerPosX -= playerSpeed;
						playerDirection = LEFT ;


					}

					if (keys[DIK_D] || keys[DIK_RIGHT]) {

						playerPosX += playerSpeed;
						playerDirection = RIGHT ;


					}

					if (keys[DIK_W] && preKeys[DIK_W] || keys[DIK_UP] && preKeys[DIK_UP] ||
						keys[DIK_S] && preKeys[DIK_S] || keys[DIK_DOWN] && preKeys[DIK_DOWN] ||
						keys[DIK_A] && preKeys[DIK_A] || keys[DIK_LEFT] && preKeys[DIK_LEFT] ||
						keys[DIK_D] && preKeys[DIK_D] || keys[DIK_RIGHT] && preKeys[DIK_RIGHT]) {

						playerMove = true;

					} else {

						playerMove = false;

					}

					//　自機が画面外に出ない様にする処理
					if (playerPosX - playerWidth <= 0) {

						playerPosX += playerSpeed;

					}

					if (playerPosX + playerWidth >= 1960) {

						playerPosX -= playerSpeed;

					}

					if (playerPosY - playerHeight <= 0) {

						playerPosY += playerSpeed;

					}

					if (playerPosY + playerHeight >= 1080) {

						playerPosY -= playerSpeed;

					}

					//　自機と敵機の当たり判定
					if (enemyLeftPosX < playerRightPosX && playerLeftPosX < enemyRightPosX) {

						isHitX = true;

					} else {

						isHitX = false;

					}

					if (enemyTopPosY < playerBottomPosY && playerTopPosY < enemyBottomPosY) {

						isHitY = true;

					} else {

						isHitY = false;

					}

					if (isHitX && isHitY) {

						isHitEnemy = true;

					} else {

						isHitEnemy = false;

					}

					//　ステージ3の当たり判定

					//　ステージ3のX座標
					for (int z = 0; z < 9; z++) {
						if (playerRightPosX > obj3LeftPosX[z]) {

							if (playerRightPosX < obj3RightPosX[z]) {

								if (playerBottomPosY > obj3TopPosY[z] && playerTopPosY < obj3BottomPosY[z]) {

									playerPosX -= playerSpeed;

								}
							}
						}

						if (playerLeftPosX < obj3RightPosX[z]) {

							if (playerLeftPosX > obj3LeftPosX[z]) {

								if (playerBottomPosY > obj3TopPosY[z] && playerTopPosY < obj3BottomPosY[z]) {

									playerPosX += playerSpeed;

								}
							}
						}
					}

					//　ステージ3のY座標
					for (int m = 0; m < 9; m++) {

						if (obj3LeftPosX[m] < playerRightPosX - 5) {

							if (obj3RightPosX[m] > playerLeftPosX + 5) {

								if (playerTopPosY < obj3TopPosY[m]) {

									if (obj3TopPosY[m] - 5 < playerBottomPosY) {

										playerPosY -= playerSpeed;

									}
								}
							}
						}

						if (obj3LeftPosX[m] < playerRightPosX - 5) {

							if (obj3RightPosX[m] > playerLeftPosX + 5) {

								if (playerBottomPosY > obj3BottomPosY[m]) {

									if (obj3BottomPosY[m] + 5 > playerTopPosY) {

										playerPosY += playerSpeed;

									}
								}
							}
						}
					}

					//　敵が振り向く処理
					if (enemyTurnTimer > 0) {

						enemyTurnTimer--;
					}

					if (enemyTurnTimer == 0) {

						enemyStopTimer--;
					}

					if (enemyStopTimer == 0) {

						enemyTurnTimer = 300;

						enemyStopTimer = 180;

					}

					//　時間を減らしていく処理
					if (countTimer > 0) {

						countTimer--;

					}

					//　クリア、オーバー画面に移る処理
					if (isHitEnemy) {

						sceneNum = clear13;
					}

					if (enemyTurnTimer == 0) {

						if (playerMove) {

							sceneNum = over13;
						}
					}

					if (countTimer == 0) {

						sceneNum = over13;

					}
					break;


			case clear11:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = title;

				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT]==false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = clear21;

				}
				break;

			case clear21:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = redyStage1;

					playerPosX = 150.0f;
					playerPosY = 540.0f;
					enemyTurnTimer = 300.0f;
					enemyStopTimer = 180.0f;
					countTimer = 1800.0f;
					redyCount = 240;

					Novice::StopAudio(stageBGM);


				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = clear11;

				}
				break;

			case clear12:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = title;

					Novice::StopAudio(stageBGM);

				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = clear22;

				}
				break;

			case clear22:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = redyStage2;

					playerPosX = 150.0f;
					playerPosY = 540.0f;
					enemyTurnTimer = 300.0f;
					enemyStopTimer = 180.0f;
					countTimer = 1800.0f;
					redyCount = 240;

					Novice::StopAudio(stageBGM);


				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = clear12;

				}
				break;

			case clear13:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = title;

					Novice::StopAudio(stageBGM);

				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = clear23;

				}
				break;

			case clear23:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = redyStage3;

					playerPosX = 150.0f;
					playerPosY = 540.0f;
					enemyTurnTimer = 300.0f;
					enemyStopTimer = 180.0f;
					countTimer = 1800.0f;
					redyCount = 240;

					Novice::StopAudio(stageBGM);


				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = clear13;

				}
				break;

			case over11:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = title;

					Novice::StopAudio(stageBGM);

				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = over21;

				}
				break;

			case over21:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = redyStage1;

					playerPosX = 150.0f;
					playerPosY = 540.0f;
					enemyTurnTimer = 300.0f;
					enemyStopTimer = 180.0f;
					countTimer = 1800.0f;
					redyCount = 240;

					Novice::StopAudio(stageBGM);


				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = over11;

				}
				break;

			case over12:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = title;
					Novice::StopAudio(stageBGM);

				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = over22;

				}
				break;

			case over22:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = redyStage2;

					playerPosX = 150.0f;
					playerPosY = 540.0f;
					enemyTurnTimer = 300.0f;
					enemyStopTimer = 180.0f;
					countTimer = 1800.0f;
					redyCount = 240;

					Novice::StopAudio(stageBGM);

				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = over12;

				}
				break;

			case over13:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = title;
					Novice::StopAudio(stageBGM);

				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = over23;

				}
				break;

			case over23:

				if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

					sceneNum = redyStage3;

					playerPosX = 150.0f;
					playerPosY = 540.0f;
					enemyTurnTimer = 300.0f;
					enemyStopTimer = 180.0f;
					countTimer = 1800.0f;
					redyCount = 240;

					Novice::StopAudio(stageBGM);


				}

				if (keys[DIK_RIGHT] && preKeys[DIK_RIGHT] == false || keys[DIK_D] && preKeys[DIK_D] == false ||
					keys[DIK_LEFT] && preKeys[DIK_LEFT] == false || keys[DIK_A] && preKeys[DIK_A] == false) {

					sceneNum = over13;

				}
				break;

		}
		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		switch (sceneNum) {

		case title:

				Novice::DrawSprite(0, 0, titleGH, 1.0f, 1.0f, 0.0f, WHITE);

				Novice::PlayAudio(titleBGM, 1, 0.2f);

			break;

		case stageSelect1:

			Novice::DrawSprite(0, 0, selectStage1GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case stageSelect2:

			Novice::DrawSprite(0, 0, selectStage2GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case stageSelect3:

			Novice::DrawSprite(0, 0, selectStage3GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case redyStage1:

			if (redyCount < 240 && redyCount>180) {

				Novice::DrawSprite(0, 0, redyNumberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

			} else if (redyCount < 180 && redyCount>120) {

				Novice::DrawSprite(0, 0, redyNumberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

			} else if (redyCount < 120 && redyCount>60) {

				Novice::DrawSprite(0, 0, redyNumberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

			} else if (redyCount < 60) {

				Novice::DrawSprite(0, 0, redyStartGH, 1.0f, 1.0f, 0.0f, WHITE);

			}
			break;

		case redyStage2:

			if (redyCount < 240 && redyCount>180) {

				Novice::DrawSprite(0, 0, redyNumberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

			} else if (redyCount < 180 && redyCount>120) {

				Novice::DrawSprite(0, 0, redyNumberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

			} else if (redyCount < 120 && redyCount>60) {

				Novice::DrawSprite(0, 0, redyNumberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

			} else if (redyCount < 60) {

				Novice::DrawSprite(0, 0, redyStartGH, 1.0f, 1.0f, 0.0f, WHITE);

			}
			break;

		case redyStage3:

			if (redyCount < 240 && redyCount>180) {

				Novice::DrawSprite(0, 0, redyNumberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

			} else if (redyCount < 180 && redyCount>120) {

				Novice::DrawSprite(0, 0, redyNumberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

			} else if (redyCount < 120 && redyCount>60) {

				Novice::DrawSprite(0, 0, redyNumberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

			} else if (redyCount < 60) {

				Novice::DrawSprite(0, 0, redyStartGH, 1.0f, 1.0f, 0.0f, WHITE);

			}
			break;

		case stage1:

			Novice::DrawSprite(0, 0, stage1GH, 1.0f, 1.0f, 0.0f, WHITE);

			Novice::PlayAudio(stageBGM, 1, 0.2f);

			if (playerDirection == UP && playerMove == false) {
				Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
					(int)playerRightPosX, (int)playerTopPosY,
					(int)playerLeftPosX, (int)playerBottomPosY,
					(int)playerRightPosX, (int)playerBottomPosY,
					0, 0, 80, 80, playerBackGH[0], WHITE);
			}
			
			if (playerDirection == UP&&playerMove) {
				if (playerTimer > 0 && playerTimer < 16) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerBackGH[0], WHITE);
				}
			}

			if (playerDirection == UP && playerMove) {
				if (playerTimer > 16 && playerTimer < 31) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerBackGH[1], WHITE);
				}
			}

			if (playerDirection == UP && playerMove) {
				if (playerTimer > 31 && playerTimer < 46) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerBackGH[0], WHITE);
				}
			}

			if (playerDirection == UP && playerMove) {
				if (playerTimer > 46 && playerTimer < 60) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerBackGH[2], WHITE);
				}
			}

			if (playerDirection == DOWN && playerMove == false) {
				Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
					(int)playerRightPosX, (int)playerTopPosY,
					(int)playerLeftPosX, (int)playerBottomPosY,
					(int)playerRightPosX, (int)playerBottomPosY,
					0, 0, 80, 80, playerFrontGH[0], WHITE);
			}

			if (playerDirection == DOWN && playerMove) {
				if (playerTimer > 0 && playerTimer < 16) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerFrontGH[0], WHITE);
				}
			}

			if (playerDirection == DOWN && playerMove) {
				if (playerTimer > 16 && playerTimer < 31) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerFrontGH[1], WHITE);
				}
			}

			if (playerDirection == DOWN && playerMove) {
				if (playerTimer > 31 && playerTimer < 46) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerFrontGH[0], WHITE);
				}
			}

			if (playerDirection == DOWN && playerMove) {
				if (playerTimer > 46 && playerTimer < 60) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerFrontGH[2], WHITE);
				}
			}

			if (playerDirection == RIGHT && playerMove == false) {
				Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
					(int)playerRightPosX, (int)playerTopPosY,
					(int)playerLeftPosX, (int)playerBottomPosY,
					(int)playerRightPosX, (int)playerBottomPosY,
					0, 0, 80, 80, playerRightGH[0], WHITE);
			}

			if (playerDirection == RIGHT && playerMove) {
				if (playerTimer > 0 && playerTimer < 16) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerRightGH[0], WHITE);
				}
			}

			if (playerDirection == RIGHT && playerMove) {
				if (playerTimer > 16 && playerTimer < 31) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerRightGH[1], WHITE);
				}
			}

			if (playerDirection == RIGHT && playerMove) {
				if (playerTimer > 31 && playerTimer < 46) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerRightGH[0], WHITE);
				}
			}

			if (playerDirection == RIGHT && playerMove) {
				if (playerTimer > 46 && playerTimer < 60) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerRightGH[2], WHITE);
				}
			}

			if (playerDirection == LEFT && playerMove == false) {
				Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
					(int)playerRightPosX, (int)playerTopPosY,
					(int)playerLeftPosX, (int)playerBottomPosY,
					(int)playerRightPosX, (int)playerBottomPosY,
					0, 0, 80, 80, playerLeftGH[0], WHITE);
			}

			if (playerDirection == LEFT && playerMove) {
				if (playerTimer > 0 && playerTimer < 16) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerLeftGH[0], WHITE);
				}
			}

			if (playerDirection == LEFT && playerMove) {
				if (playerTimer > 16 && playerTimer < 31) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerLeftGH[1], WHITE);
				}
			}

			if (playerDirection == LEFT && playerMove) {
				if (playerTimer > 31 && playerTimer < 46) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerLeftGH[0], WHITE);
				}
			}

			if (playerDirection == LEFT && playerMove) {
				if (playerTimer > 46 && playerTimer < 60) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerLeftGH[2], WHITE);
				}
			}

			if (enemyTurnTimer > 0) {

				Novice::DrawQuad((int)enemyLeftPosX, (int)enemyTopPosY,
					(int)enemyRightPosX, (int)enemyTopPosY,
					(int)enemyLeftPosX, (int)enemyBottomPosY,
					(int)enemyRightPosX, (int)enemyBottomPosY,
					0, 0, 80, 80, enemyGH[1], WHITE);

			} else if (enemyTurnTimer == 0) {

				Novice::DrawQuad((int)enemyLeftPosX, (int)enemyTopPosY,
					(int)enemyRightPosX, (int)enemyTopPosY,
					(int)enemyLeftPosX, (int)enemyBottomPosY,
					(int)enemyRightPosX, (int)enemyBottomPosY,
					0, 0, 80, 80, enemyGH[0], WHITE);

			}

			for (int i = 0; i < 2; i++) {
				Novice::DrawQuad((int)obj1LeftPosX[i], (int)obj1TopPosY[i],
					(int)obj1RightPosX[i], (int)obj1TopPosY[i],
					(int)obj1LeftPosX[i], (int)obj1BottomPosY[i],
					(int)obj1RightPosX[i], (int)obj1BottomPosY[i],
					0, 0, 32, 32, objStage1, WHITE);
			}

			Novice::DrawQuad((int)obj1LeftPosX[2], (int)obj1TopPosY[2],
				(int)obj1RightPosX[2], (int)obj1TopPosY[2],
				(int)obj1LeftPosX[2], (int)obj1BottomPosY[2],
				(int)obj1RightPosX[2], (int)obj1BottomPosY[2],
				0, 0, 32, 32, centerObjStage1, WHITE);

			for (int i = 3; i < 5; i++) {
				Novice::DrawQuad((int)obj1LeftPosX[i], (int)obj1TopPosY[i],
					(int)obj1RightPosX[i], (int)obj1TopPosY[i],
					(int)obj1LeftPosX[i], (int)obj1BottomPosY[i],
					(int)obj1RightPosX[i], (int)obj1BottomPosY[i],
					0, 0, 32, 32, objStage1, WHITE);
			}

			Novice::DrawSprite(40, 30, timerGH, 2.0f, 2.0f, 0.0f, WHITE);

			if (enemyTurnTimer < 300 && enemyTurnTimer>240) {

				Novice::DrawSprite(980-32, 50, numberGH[5], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer < 240 && enemyTurnTimer>180) {

				Novice::DrawSprite(980-32, 50, numberGH[4], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer < 180 && enemyTurnTimer>120) {

				Novice::DrawSprite(980-32, 50, numberGH[3], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer < 120 && enemyTurnTimer>60) {

				Novice::DrawSprite(980-32, 50, numberGH[2], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer < 60&&enemyTurnTimer>1) {

				Novice::DrawSprite(980-32, 50, numberGH[1], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer == 0) {

				Novice::DrawSprite(0, 50, stopGH, 1.0f, 1.0f, 0.0f, WHITE);
			}

			if (countTimer < 1800&&countTimer>1740) {

				Novice::DrawSprite(110, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

			}

			

			if (countTimer < 1740&&countTimer>1680) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[9], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1680 && countTimer>1620) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[8], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1620 && countTimer>1560) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[7], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1560 && countTimer>1500) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[6], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1500 && countTimer>1440) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[5], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1440 && countTimer>1380) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[4], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1380 && countTimer>1320) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1320 && countTimer>1260) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1260 && countTimer>1200) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1200 && countTimer>1140) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1140 && countTimer>1080) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[9], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1080 && countTimer>1020) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[8], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1020 && countTimer>960) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[7], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 960 && countTimer>900) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[6], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 900 && countTimer>840) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[5], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 840 && countTimer>780) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[4], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 780 && countTimer>720) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 720 && countTimer>660) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 660 && countTimer>600) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 600 && countTimer>540) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 540 && countTimer>480) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[9], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 480 && countTimer>420) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[8], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 420 && countTimer>360) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[7], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 360 && countTimer>300) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[6], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 300 && countTimer>240) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[5], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 240 && countTimer>180) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[4], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 180 && countTimer>120) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 120 && countTimer>60) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 60) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

			}

			break;

			case stage2:

				Novice::DrawSprite(0, 0, stage1GH, 1.0f, 1.0f, 0.0f, WHITE);

				if (playerDirection == UP && playerMove == false) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerBackGH[0], WHITE);
				}

				if (playerDirection == UP && playerMove) {
					if (playerTimer > 0 && playerTimer < 16) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerBackGH[0], WHITE);
					}
				}

				if (playerDirection == UP && playerMove) {
					if (playerTimer > 16 && playerTimer < 31) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerBackGH[1], WHITE);
					}
				}

				if (playerDirection == UP && playerMove) {
					if (playerTimer > 31 && playerTimer < 46) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerBackGH[0], WHITE);
					}
				}

				if (playerDirection == UP && playerMove) {
					if (playerTimer > 46 && playerTimer < 60) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerBackGH[2], WHITE);
					}
				}

				if (playerDirection == DOWN && playerMove == false) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerFrontGH[0], WHITE);
				}

				if (playerDirection == DOWN && playerMove) {
					if (playerTimer > 0 && playerTimer < 16) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerFrontGH[0], WHITE);
					}
				}

				if (playerDirection == DOWN && playerMove) {
					if (playerTimer > 16 && playerTimer < 31) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerFrontGH[1], WHITE);
					}
				}

				if (playerDirection == DOWN && playerMove) {
					if (playerTimer > 31 && playerTimer < 46) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerFrontGH[0], WHITE);
					}
				}

				if (playerDirection == DOWN && playerMove) {
					if (playerTimer > 46 && playerTimer < 60) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerFrontGH[2], WHITE);
					}
				}

				if (playerDirection == RIGHT && playerMove == false) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerRightGH[0], WHITE);
				}

				if (playerDirection == RIGHT && playerMove) {
					if (playerTimer > 0 && playerTimer < 16) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerRightGH[0], WHITE);
					}
				}

				if (playerDirection == RIGHT && playerMove) {
					if (playerTimer > 16 && playerTimer < 31) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerRightGH[1], WHITE);
					}
				}

				if (playerDirection == RIGHT && playerMove) {
					if (playerTimer > 31 && playerTimer < 46) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerRightGH[0], WHITE);
					}
				}

				if (playerDirection == RIGHT && playerMove) {
					if (playerTimer > 46 && playerTimer < 60) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerRightGH[2], WHITE);
					}
				}

				if (playerDirection == LEFT && playerMove == false) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerLeftGH[0], WHITE);
				}

				if (playerDirection == LEFT && playerMove) {
					if (playerTimer > 0 && playerTimer < 16) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerLeftGH[0], WHITE);
					}
				}

				if (playerDirection == LEFT && playerMove) {
					if (playerTimer > 16 && playerTimer < 31) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerLeftGH[1], WHITE);
					}
				}

				if (playerDirection == LEFT && playerMove) {
					if (playerTimer > 31 && playerTimer < 46) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerLeftGH[0], WHITE);
					}
				}

				if (playerDirection == LEFT && playerMove) {
					if (playerTimer > 46 && playerTimer < 60) {
						Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
							(int)playerRightPosX, (int)playerTopPosY,
							(int)playerLeftPosX, (int)playerBottomPosY,
							(int)playerRightPosX, (int)playerBottomPosY,
							0, 0, 80, 80, playerLeftGH[2], WHITE);
					}
				}

				if (enemyTurnTimer > 0) {

					Novice::DrawQuad((int)enemyLeftPosX, (int)enemyTopPosY,
						(int)enemyRightPosX, (int)enemyTopPosY,
						(int)enemyLeftPosX, (int)enemyBottomPosY,
						(int)enemyRightPosX, (int)enemyBottomPosY,
						0, 0, 80, 80, enemyGH[1], WHITE);

				} else if (enemyTurnTimer == 0) {

					Novice::DrawQuad((int)enemyLeftPosX, (int)enemyTopPosY,
						(int)enemyRightPosX, (int)enemyTopPosY,
						(int)enemyLeftPosX, (int)enemyBottomPosY,
						(int)enemyRightPosX, (int)enemyBottomPosY,
						0, 0, 80, 80, enemyGH[0], WHITE);

				}

					Novice::DrawQuad((int)obj2LeftPosX[0], (int)obj2TopPosY[0],
						(int)obj2RightPosX[0], (int)obj2TopPosY[0],
						(int)obj2LeftPosX[0], (int)obj2BottomPosY[0],
						(int)obj2RightPosX[0], (int)obj2BottomPosY[0],
						0, 0, 32, 32, objStage2W, WHITE);

					Novice::DrawQuad((int)obj2LeftPosX[2], (int)obj2TopPosY[2],
						(int)obj2RightPosX[2], (int)obj2TopPosY[2],
						(int)obj2LeftPosX[2], (int)obj2BottomPosY[2],
						(int)obj2RightPosX[2], (int)obj2BottomPosY[2],
						0, 0, 32, 32, objStage2W, WHITE);

					Novice::DrawQuad((int)obj2LeftPosX[3], (int)obj2TopPosY[3],
						(int)obj2RightPosX[3], (int)obj2TopPosY[3],
						(int)obj2LeftPosX[3], (int)obj2BottomPosY[3],
						(int)obj2RightPosX[3], (int)obj2BottomPosY[3],
						0, 0, 32, 32, objStage2W, WHITE);

					Novice::DrawQuad((int)obj2LeftPosX[4], (int)obj2TopPosY[4],
						(int)obj2RightPosX[4], (int)obj2TopPosY[4],
						(int)obj2LeftPosX[4], (int)obj2BottomPosY[4],
						(int)obj2RightPosX[4], (int)obj2BottomPosY[4],
						0, 0, 32, 32, objStage2W, WHITE);

					Novice::DrawQuad((int)obj2LeftPosX[7], (int)obj2TopPosY[7],
						(int)obj2RightPosX[7], (int)obj2TopPosY[7],
						(int)obj2LeftPosX[7], (int)obj2BottomPosY[7],
						(int)obj2RightPosX[7], (int)obj2BottomPosY[7],
						0, 0, 32, 32, objStage2W, WHITE);

					Novice::DrawQuad((int)obj2LeftPosX[1], (int)obj2TopPosY[1],
						(int)obj2RightPosX[1], (int)obj2TopPosY[1],
						(int)obj2LeftPosX[1], (int)obj2BottomPosY[1],
						(int)obj2RightPosX[1], (int)obj2BottomPosY[1],
						0, 0, 32, 32, objStage2H, WHITE);

					Novice::DrawQuad((int)obj2LeftPosX[5], (int)obj2TopPosY[5],
						(int)obj2RightPosX[5], (int)obj2TopPosY[5],
						(int)obj2LeftPosX[5], (int)obj2BottomPosY[5],
						(int)obj2RightPosX[5], (int)obj2BottomPosY[5],
						0, 0, 32, 32, objStage2W, WHITE);

					Novice::DrawQuad((int)obj2LeftPosX[6], (int)obj2TopPosY[6],
						(int)obj2RightPosX[6], (int)obj2TopPosY[6],
						(int)obj2LeftPosX[6], (int)obj2BottomPosY[6],
						(int)obj2RightPosX[6], (int)obj2BottomPosY[6],
						0, 0, 32, 32, objStage2W, WHITE);

					Novice::DrawQuad((int)obj2LeftPosX[8], (int)obj2TopPosY[8],
						(int)obj2RightPosX[8], (int)obj2TopPosY[8],
						(int)obj2LeftPosX[8], (int)obj2BottomPosY[8],
						(int)obj2RightPosX[8], (int)obj2BottomPosY[8],
						0, 0, 32, 32, objStage2W, WHITE);

				Novice::DrawSprite(40, 30, timerGH, 2.0f, 2.0f, 0.0f, WHITE);

				if (enemyTurnTimer < 300 && enemyTurnTimer>240) {

					Novice::DrawSprite(980 - 32, 50, numberGH[5], 1.5f, 1.5f, 0.0f, WHITE);

				}

				if (enemyTurnTimer < 240 && enemyTurnTimer>180) {

					Novice::DrawSprite(980 - 32, 50, numberGH[4], 1.5f, 1.5f, 0.0f, WHITE);

				}

				if (enemyTurnTimer < 180 && enemyTurnTimer>120) {

					Novice::DrawSprite(980 - 32, 50, numberGH[3], 1.5f, 1.5f, 0.0f, WHITE);

				}

				if (enemyTurnTimer < 120 && enemyTurnTimer>60) {

					Novice::DrawSprite(980 - 32, 50, numberGH[2], 1.5f, 1.5f, 0.0f, WHITE);

				}

				if (enemyTurnTimer < 60 && enemyTurnTimer>1) {

					Novice::DrawSprite(980 - 32, 50, numberGH[1], 1.5f, 1.5f, 0.0f, WHITE);

				}

				if (enemyTurnTimer == 0) {

					Novice::DrawSprite(0, 40, stopGH, 1.0f, 1.0f, 0.0f, WHITE);
				}

				if (countTimer < 1800 && countTimer>1741) {

					Novice::DrawSprite(110, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				}



				if (countTimer < 1740 && countTimer>1680) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[9], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1680 && countTimer>1620) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[8], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1620 && countTimer>1560) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[7], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1560 && countTimer>1500) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[6], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1500 && countTimer>1440) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[5], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1440 && countTimer>1380) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[4], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1380 && countTimer>1320) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1320 && countTimer>1260) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1260 && countTimer>1200) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1200 && countTimer>1140) {

					Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1140 && countTimer>1080) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[9], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1080 && countTimer>1020) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[8], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 1020 && countTimer>960) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[7], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 960 && countTimer>900) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[6], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 900 && countTimer>840) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[5], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 840 && countTimer>780) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[4], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 780 && countTimer>720) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 720 && countTimer>660) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 660 && countTimer>600) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 600 && countTimer>540) {

					Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 540 && countTimer>480) {

					Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[9], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 480 && countTimer>420) {

					Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[8], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 420 && countTimer>360) {

					Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[7], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 360 && countTimer>300) {

					Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[6], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 300 && countTimer>240) {

					Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[5], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 240 && countTimer>180) {

					Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[4], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 180 && countTimer>120) {

					Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 120 && countTimer>60) {

					Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				}

				if (countTimer < 60) {

					Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

					Novice::DrawSprite(145, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				}

				break;

		case stage3:

			Novice::DrawSprite(0, 0, stage1GH, 1.0f, 1.0f, 0.0f, WHITE);

			if (playerDirection == UP && playerMove == false) {
				Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
					(int)playerRightPosX, (int)playerTopPosY,
					(int)playerLeftPosX, (int)playerBottomPosY,
					(int)playerRightPosX, (int)playerBottomPosY,
					0, 0, 80, 80, playerBackGH[0], WHITE);
			}

			if (playerDirection == UP && playerMove) {
				if (playerTimer > 0 && playerTimer < 16) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerBackGH[0], WHITE);
				}
			}

			if (playerDirection == UP && playerMove) {
				if (playerTimer > 16 && playerTimer < 31) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerBackGH[1], WHITE);
				}
			}

			if (playerDirection == UP && playerMove) {
				if (playerTimer > 31 && playerTimer < 46) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerBackGH[0], WHITE);
				}
			}

			if (playerDirection == UP && playerMove) {
				if (playerTimer > 46 && playerTimer < 60) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerBackGH[2], WHITE);
				}
			}

			if (playerDirection == DOWN && playerMove == false) {
				Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
					(int)playerRightPosX, (int)playerTopPosY,
					(int)playerLeftPosX, (int)playerBottomPosY,
					(int)playerRightPosX, (int)playerBottomPosY,
					0, 0, 80, 80, playerFrontGH[0], WHITE);
			}

			if (playerDirection == DOWN && playerMove) {
				if (playerTimer > 0 && playerTimer < 16) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerFrontGH[0], WHITE);
				}
			}

			if (playerDirection == DOWN && playerMove) {
				if (playerTimer > 16 && playerTimer < 31) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerFrontGH[1], WHITE);
				}
			}

			if (playerDirection == DOWN && playerMove) {
				if (playerTimer > 31 && playerTimer < 46) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerFrontGH[0], WHITE);
				}
			}

			if (playerDirection == DOWN && playerMove) {
				if (playerTimer > 46 && playerTimer < 60) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerFrontGH[2], WHITE);
				}
			}

			if (playerDirection == RIGHT && playerMove == false) {
				Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
					(int)playerRightPosX, (int)playerTopPosY,
					(int)playerLeftPosX, (int)playerBottomPosY,
					(int)playerRightPosX, (int)playerBottomPosY,
					0, 0, 80, 80, playerRightGH[0], WHITE);
			}

			if (playerDirection == RIGHT && playerMove) {
				if (playerTimer > 0 && playerTimer < 16) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerRightGH[0], WHITE);
				}
			}

			if (playerDirection == RIGHT && playerMove) {
				if (playerTimer > 16 && playerTimer < 31) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerRightGH[1], WHITE);
				}
			}

			if (playerDirection == RIGHT && playerMove) {
				if (playerTimer > 31 && playerTimer < 46) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerRightGH[0], WHITE);
				}
			}

			if (playerDirection == RIGHT && playerMove) {
				if (playerTimer > 46 && playerTimer < 60) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerRightGH[2], WHITE);
				}
			}

			if (playerDirection == LEFT && playerMove == false) {
				Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
					(int)playerRightPosX, (int)playerTopPosY,
					(int)playerLeftPosX, (int)playerBottomPosY,
					(int)playerRightPosX, (int)playerBottomPosY,
					0, 0, 80, 80, playerLeftGH[0], WHITE);
			}

			if (playerDirection == LEFT && playerMove) {
				if (playerTimer > 0 && playerTimer < 16) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerLeftGH[0], WHITE);
				}
			}

			if (playerDirection == LEFT && playerMove) {
				if (playerTimer > 16 && playerTimer < 31) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerLeftGH[1], WHITE);
				}
			}

			if (playerDirection == LEFT && playerMove) {
				if (playerTimer > 31 && playerTimer < 46) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerLeftGH[0], WHITE);
				}
			}

			if (playerDirection == LEFT && playerMove) {
				if (playerTimer > 46 && playerTimer < 60) {
					Novice::DrawQuad((int)playerLeftPosX, (int)playerTopPosY,
						(int)playerRightPosX, (int)playerTopPosY,
						(int)playerLeftPosX, (int)playerBottomPosY,
						(int)playerRightPosX, (int)playerBottomPosY,
						0, 0, 80, 80, playerLeftGH[2], WHITE);
				}
			}

			if (enemyTurnTimer > 0) {

				Novice::DrawQuad((int)enemyLeftPosX, (int)enemyTopPosY,
					(int)enemyRightPosX, (int)enemyTopPosY,
					(int)enemyLeftPosX, (int)enemyBottomPosY,
					(int)enemyRightPosX, (int)enemyBottomPosY,
					0, 0, 80, 80, enemyGH[1], WHITE);

			} else if (enemyTurnTimer == 0) {

				Novice::DrawQuad((int)enemyLeftPosX, (int)enemyTopPosY,
					(int)enemyRightPosX, (int)enemyTopPosY,
					(int)enemyLeftPosX, (int)enemyBottomPosY,
					(int)enemyRightPosX, (int)enemyBottomPosY,
					0, 0, 80, 80, enemyGH[0], WHITE);

			}

			for (int i = 0; i < 9; i++) {
				Novice::DrawQuad((int)obj3LeftPosX[i], (int)obj3TopPosY[i],
					(int)obj3RightPosX[i], (int)obj3TopPosY[i],
					(int)obj3LeftPosX[i], (int)obj3BottomPosY[i],
					(int)obj3RightPosX[i], (int)obj3BottomPosY[i],
					0, 0, 32, 32, obj3GH, WHITE);
			}

			Novice::DrawSprite(40, 30, timerGH, 2.0f, 2.0f, 0.0f, WHITE);

			if (enemyTurnTimer < 300 && enemyTurnTimer>240) {

				Novice::DrawSprite(980 - 32, 50, numberGH[5], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer < 240 && enemyTurnTimer>180) {

				Novice::DrawSprite(980 - 32, 50, numberGH[4], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer < 180 && enemyTurnTimer>120) {

				Novice::DrawSprite(980 - 32, 50, numberGH[3], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer < 120 && enemyTurnTimer>60) {

				Novice::DrawSprite(980 - 32, 50, numberGH[2], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer < 60 && enemyTurnTimer>1) {

				Novice::DrawSprite(980 - 32, 50, numberGH[1], 1.5f, 1.5f, 0.0f, WHITE);

			}

			if (enemyTurnTimer == 0) {

				Novice::DrawSprite(-5, 50, stopGH, 1.0f, 1.0f, 0.0f, WHITE);
			}

			if (countTimer < 1800 && countTimer>1740) {

				Novice::DrawSprite(110, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

			}



			if (countTimer < 1740 && countTimer>1680) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[9], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1680 && countTimer>1620) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[8], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1620 && countTimer>1560) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[7], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1560 && countTimer>1500) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[6], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1500 && countTimer>1440) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[5], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1440 && countTimer>1380) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[4], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1380 && countTimer>1320) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1320 && countTimer>1260) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1260 && countTimer>1200) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1200 && countTimer>1140) {

				Novice::DrawSprite(110, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1140 && countTimer>1080) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[9], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1080 && countTimer>1020) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[8], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 1020 && countTimer>960) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[7], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 960 && countTimer>900) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[6], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 900 && countTimer>840) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[5], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 840 && countTimer>780) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[4], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 780 && countTimer>720) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 720 && countTimer>660) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 660 && countTimer>600) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 600 && countTimer>540) {

				Novice::DrawSprite(110, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 540 && countTimer>480) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[9], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 480 && countTimer>420) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[8], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 420 && countTimer>360) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[7], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 360 && countTimer>300) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[6], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 300 && countTimer>240) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[5], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 240 && countTimer>180) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[4], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 180 && countTimer>120) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[3], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 120 && countTimer>60) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[2], 1.0f, 1.0f, 0.0f, WHITE);

			}

			if (countTimer < 60) {

				Novice::DrawSprite(110, 30, numberGH[0], 1.0f, 1.0f, 0.0f, WHITE);

				Novice::DrawSprite(145, 30, numberGH[1], 1.0f, 1.0f, 0.0f, WHITE);

			}

			
			break;

		case clear11:

			Novice::DrawSprite(0, 0, clear1GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case clear21:

			Novice::DrawSprite(0, 0, clear2GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case clear12:

			Novice::DrawSprite(0, 0, clear1GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case clear22:

			Novice::DrawSprite(0, 0, clear2GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case clear13:

			Novice::DrawSprite(0, 0, clear1GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case clear23:

			Novice::DrawSprite(0, 0, clear2GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case over11:

			Novice::DrawSprite(0, 0, over1GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case over21:

			Novice::DrawSprite(0, 0, over2GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case over12:

			Novice::DrawSprite(0, 0, over1GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case over22:

			Novice::DrawSprite(0, 0, over2GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;
			
		case over13:

			Novice::DrawSprite(0, 0, over1GH, 1.0f, 1.0f, 0.0f, WHITE);

			break;

		case over23:

			Novice::DrawSprite(0, 0, over2GH, 1.0f, 1.0f, 0.0f, WHITE);

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
