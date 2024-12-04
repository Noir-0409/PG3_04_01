#include <Novice.h>
#include <stdlib.h>
#include <time.h>
#include "Vector2.h"
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "TR1-1";

//変数

//プレイヤー
struct Player {

	float x;
	float y;
	float radius;
	float speed;

};

Player player{

	522.0f,
	342.0f,
	16.0f,
	36.0f,

};

//マップチップ

//1マスのサイズ
int size_map_x = 36;
int size_map_y = 36;

//縦横の個数
int num_map_x = 30;
int num_map_y = 20;

int map[20][30] = {

	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,

	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0, 0,0,0,0,0,0,0,0,0,0,

	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,
	1,1,1,1,1,1,1,1,1,1, 0,0,0,0,0,0,0,0,0,0, 1,1,1,1,1,1,1,1,1,1,


};

//フラグ

//プレイヤーがエンカウントエリアにいるかどうか
int player_in_encounter_area = false;

int player_left_move = false;

int player_right_move = false;

int player_up_move = false;

int player_down_move = false;

//エンカウントの発生
int is_encount = false;

//エンカウント率
int encount_chance = 0;

float posX[6] = { 0.0f };
float posY[6] = { 60.0f,180.0,300.0f,420.0f,540.0f,660.0f };
float leftTopX[6] = { 0.0f };
float leftTopY[6] = { 0.0f };
float width = 1080.0f;
float height = 120.0f;

float startX[6] = { -1080.0f,-1280.0f,-1580.0f,-1880.0f,-2180.0f,-2480.0f };
float endX = 540.0f;
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


// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1080, 720);

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

		//プレイヤーがエンカウントエリア(マップの1の部分)に入ったらtrueにする
		if (player.x <= 360 && player.y <= 252) {

			player_in_encounter_area = true;

		} else if (player.x >= 720 && player.y <= 252) {

			player_in_encounter_area = true;

		}else if(player.x<=360&&player.y>=468) {

			player_in_encounter_area = true;

		} else if (player.x >= 720 && player.y >= 468) {

			player_in_encounter_area = true;

		}else {

			player_in_encounter_area = false;

		}

		//プレイヤーの移動処理
		if (keys[DIK_A] && preKeys[DIK_A] == false) {

			player.x -= player.speed;

			player_left_move = true;

		} else if (keys[DIK_A] == false) {

			player_left_move = false;

		}

		if (keys[DIK_D] && preKeys[DIK_D] == false) {

			player.x += player.speed;

			player_right_move = true;

		} else if (keys[DIK_D] == false) {

			player_right_move = false;

		}

		if (keys[DIK_W] && preKeys[DIK_W] == false) {

			player.y -= player.speed;

			player_up_move = true;

		} else if (keys[DIK_W] == false) {

			player_up_move = false;

		}

		if (keys[DIK_S] && preKeys[DIK_S] == false) {

			player.y += player.speed;

			player_down_move = true;

		} else if (keys[DIK_S] == false) {

			player_down_move = false;

		}

		//プレイヤーがエンカウントエリアにいる際にencount_chanceの抽選を起こす
		if (player_in_encounter_area) {

			if (player_up_move) {

				encount_chance = rand() % 31 - 15;

			}

		}

		//プレイヤーがエンカウントエリアにいる際にencount_chanceの抽選を起こす
		if (player_in_encounter_area) {

			if (player_down_move) {

				encount_chance = rand() % 31 - 15;

			}

		}

		//プレイヤーがエンカウントエリアにいる際にencount_chanceの抽選を起こす
		if (player_in_encounter_area) {

			if (player_left_move) {

				encount_chance = rand() % 31 - 15;

			}

		}

		//プレイヤーがエンカウントエリアにいる際にencount_chanceの抽選を起こす
		if (player_in_encounter_area) {

			if (player_right_move) {

				encount_chance = rand() % 31 - 15;

			}

		}

		if (encount_chance==1) {

			is_encount = true;

		}

		// エンカウント時の状態遷移
		if (is_encount) {

			moveX = true;

			frameX = 0;

		}

		if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

			is_encount = false;

		}

		for (int i = 0; i < 6; i++) {

			leftTopX[i] = posX[i] - width / 2;
			leftTopY[i] = posY[i] - height / 2;

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		//背景の描画
		Novice::DrawBox(0, 0, 1080, 720, 0.0f, 0x8b4513ff, kFillModeSolid);

		//マップの描画
		for (int y = 0; y < num_map_y; y++) {

			for (int x = 0; x < num_map_x; x++) {

				if (map[y][x] == 0) {

					Novice::DrawBox(x * size_map_y, y * size_map_x, size_map_y, size_map_x, 0.0f, 0x6495edff, kFillModeWireFrame);

				}

				if (map[y][x] == 1) {

					Novice::DrawBox(x * size_map_y, y * size_map_x, size_map_y, size_map_x, 0.0f, 0x228b22ff, kFillModeSolid);

					Novice::DrawBox(x * size_map_y, y * size_map_x, size_map_y, size_map_x, 0.0f, 0xb0c4deff, kFillModeWireFrame);

				}

			}

		}

		//プレイヤーの描画
		Novice::DrawEllipse((int)player.x, (int)player.y, (int)player.radius, (int)player.radius, 0.0f, BLACK, kFillModeSolid);

		for (int i = 0; i < 6; i++) {

			Novice::DrawBox((int)leftTopX[i], (int)leftTopY[i], (int)width, (int)height, 0.0f, WHITE, kFillModeSolid);

		}

		//デバッグ用
		//Novice::ScreenPrintf(10, 10, "player_in_encounter_area=%d", player_in_encounter_area);

		//Novice::ScreenPrintf(10, 30, "player_left_move=%d", player_left_move);

		//Novice::ScreenPrintf(10, 50, "player_right_move=%d", player_right_move);

		//Novice::ScreenPrintf(10, 70, "player_up_move=%d", player_up_move);

		//Novice::ScreenPrintf(10, 90, "player_down_move=%d", player_down_move);

		//Novice::ScreenPrintf(10, 10, "encount_chance=%d", encount_chance);

		//Novice::ScreenPrintf(10, 30, "is_encount=%d", is_encount);

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
