#include <Novice.h>
#include "Vector2.h"
#define _USE_MATH_DEFINES
#include <math.h>

float posX[6] = { 0.0f };
float posY[6] = { 60.0f,180.0,300.0f,420.0f,540.0f,660.0f };
float leftTopX[6] = { 0.0f };
float leftTopY[6] = { 0.0f };
float width = 1280.0f;
float height = 120.0f;

float startX[6] = { -1280.0f,-1580.0f,-1880.0f,-2180.0f,-2480.0f,-2780.0f };
float endX = 640.0f;
float frameX = 0.0f;
float endFrameX = 180.0f;

int moveX = false;

float easeOutBackSine(float x) {

	const double c1 = 1.70158;

	const double c3 = c1 + 1;

	return (float)1 + (float)c3 * (float)pow(x - 1, 3) + (float)c1 * (float)pow(x - 1, 2);

}

float easeOutBack(float x) {

	return easeOutBackSine(x = (frameX / endFrameX));

}


const char kWindowTitle[] = "演出評価課題";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//　変数宣言
	int size_map_x = 32; //マップチップXサイズ
	int size_map_y = 32; //マップチップYサイズ

	int num_map_x = 40;
	int num_map_y = 25;

	int map1[25][40] = {

		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,
		0,1,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,1,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,
		0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
		
	};

	int randX = 0;
	int randY = 0;

	int randTimer = 120;

	int shakeX = 80;
	int shakeY = 80;

	struct Player {

		Vector2 pos;
		Vector2 speed;
		float radius;

	};

	struct Bullet {

		Vector2 pos;
		Vector2 speed;
		float radius;

	};

	Player player{

		{640.0f,360.0f},
		{7.0f,7.0f},
		40.0f,

	};

	Bullet bullet{

		{0.0f,0.0f},
		{1.0f,15.0f},
		70.0f,

	};

	int isShot = false;
	int isCharge = false;
	float chargeCount = 180.0f;

	enum scene {
		one,
		two,
		three
	};

	int sceneCount = 0;

	float p_posX[30] = { 0.0f };
	float p_posY[30] = { 0.0f };
	float p_speed[30] = { 0.0f };
	float p_radius[30] = { 0.0f };
	int isAlive[30] = { false };

	//　乱数を管理する変数
	int emitMaxX = 1281;
	int emitMinX = 640;
	int emitMaxY = 51;
	int emitMinY = 25;

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

		switch (sceneCount)
		{
		case one:
		{

			if (keys[DIK_A]) {

				player.pos.x -= player.speed.x;

			} else if (keys[DIK_D]) {

				player.pos.x += player.speed.x;

			}

			if (isShot == false) {

				if (keys[DIK_SPACE] && preKeys[DIK_SPACE]) {

					isCharge = true;

					bullet.pos.x = player.pos.x;

					bullet.pos.y = player.pos.y;

					chargeCount = 180;

					bullet.radius = 70;

					shakeX = 80;

					shakeY = 80;

					randTimer = 120;

				}

			}

			if (isCharge) {

				chargeCount--;

				randTimer--;

				shakeX--;

				shakeY--;

				if (randTimer >= 1) {

					if (shakeX >= 1 && shakeY >= 1) {

						randX = rand() % (shakeX + 1) - (shakeX / 2);

						randY = rand() % (shakeY + 1) - (shakeY / 2);

					}

				}

				if (bullet.radius >= 15) {

					bullet.radius--;

				}

			}

			if (chargeCount == 0) {

				isShot = true;

			}

			if (isShot) {

				bullet.pos.y -= bullet.speed.y;

				if (bullet.pos.y <= -50) {

					isCharge = false;

					isShot = false;

				}

			}

			if (randTimer == 0) {

				randX = 0;

				randY = 0;

			}

			if (keys[DIK_2] && preKeys[DIK_2] == false) {

				sceneCount = two;

			} else if (keys[DIK_3] && preKeys[DIK_3] == false) {

				sceneCount = three;

			}

			break;

		}
		case two:
		{

			if (keys[DIK_1] && preKeys[DIK_1] == false) {

				sceneCount = one;

			} else if (keys[DIK_3] && preKeys[DIK_3] == false) {

				sceneCount = three;

			}

			for (int i = 0; i < 6; i++) {

				leftTopX[i] = posX[i] - width / 2;
				leftTopY[i] = posY[i] - height / 2;

			}

			//自機を動かす処理
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

				moveX = true;

				frameX = 0;

			}

			if (moveX) {

				frameX++;

			}

			if (frameX >= endFrameX) {

				moveX = false;

			}

			for (int i = 0; i < 6; i++) {

				posX[i] = startX[i] + (endX - startX[i]) * easeOutBack(frameX / endFrameX);

			}

			break;

		}
		case three:
		{

			if (keys[DIK_1] && preKeys[DIK_1] == false) {

				sceneCount = one;

			} else if (keys[DIK_2] && preKeys[DIK_2] == false) {

				sceneCount = two;

			}

			// 弾を出す処理
			for (int i = 0; i < 30; i++) {

				if (isAlive[i] == false) {

					isAlive[i] = true;

					p_posX[i] = 640;

					p_posY[i] = 0;

					p_speed[i] = 8;

					p_radius[i] = 10;

					p_posX[i] = p_posX[i] + rand() % emitMaxX - emitMinX;

					p_posY[i] = p_posY[i] + rand() % emitMaxY - emitMinY;

					break;

				}

			}

			// 乱数の範囲を制御する処理
			emitMinX = emitMaxX / 2;

			emitMinY = emitMaxY / 2;

			// 弾を動かす処理
			for (int i = 0; i < 30; i++) {

				if (isAlive[i]) {

					p_posX[i] += p_speed[i];
					
					p_posY[i] += p_speed[i];

				}

				if (p_posY[i] >= 750) {

					isAlive[i] = false;

				}

			}

			break;

		}

		}
	
		///
		/// ↑更新処理ここまで
		///

		

		///
		/// ↓描画処理ここから
		///

		switch (sceneCount) {

		case one:
		{
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, 0xc0c0c0ff, kFillModeSolid);

			for (int y = 0; y < num_map_y; y++) {

				for (int x = 0; x < num_map_x; x++) {

					if (map1[y][x] == 1) {

						Novice::DrawBox(x * size_map_y + randY, y * size_map_x + randX, size_map_y, size_map_x, 0.0f, BLACK, kFillModeSolid);

					}
				}
			}

			Novice::DrawEllipse((int)player.pos.x, (int)player.pos.y, (int)player.radius, (int)player.radius, 0.0f, RED, kFillModeSolid);

			if (isCharge) {

				Novice::DrawEllipse((int)bullet.pos.x, (int)bullet.pos.y, (int)bullet.radius, (int)bullet.radius, 0.0f, BLUE, kFillModeSolid);

			}

			Novice::ScreenPrintf(10, 10, "SPACE::charge & shot");

			break;

		}

		case two:
		{

			Novice::DrawLine(0, 360, 1280, 360, BLACK);

			Novice::DrawLine(640, 0, 640, 720, BLACK);

			// 自機の描画
			for (int i = 0; i < 6; i++) {

				Novice::DrawBox((int)leftTopX[i], (int)leftTopY[i], (int)width, (int)height, 0.0f, 0xffff99ff, kFillModeSolid);

			}

			Novice::ScreenPrintf(10, 10, "SPACE::move");

			break;
		}

		case three: {

			// 背景の画像
			Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLACK, kFillModeSolid);

			// 弾の描画
			for (int i = 0; i < 30; i++) {

				if (isAlive[i]) {

					Novice::DrawEllipse((int)p_posX[i], (int)p_posY[i], (int)p_radius[i], (int)p_radius[i], 0.0f, WHITE, kFillModeSolid);

				}

			}

			break;

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
