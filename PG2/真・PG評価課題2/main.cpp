#include <Novice.h>
#include "Player.h"
#include "Enemy.h"

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);


	enum SCENE {

		title,
		play

	};

	int sceneNum = title;

	float distX = 0.0f;
	float distY = 0.0f;
	float dist = 0.0f;
	int radius = 0;

	float player_distX = 0.0f;
	float player_distY = 0.0f;
	float player_dist = 0.0f;
	int player_radius = 0;

	float enemyRespornTimer = 30.0f;
	float playerRespornTimer = 30.0f;

	int bullet_isHit = false;
	int player_isHit = false;

	Player* player = new Player();
	Enemy* enemy = new Enemy();

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

		switch (sceneNum)
		{

		case title:

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN]==false) {

				sceneNum = play;

			}

			break;

		case play:

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

				sceneNum = title;

			}

			//弾と敵の当たり判定
			distX = (float)enemy->GetPosX() - (float)player->GetBulletPosX();
			distY = (float)enemy->GetPosY() - (float)player->GetBulletPosY();
			dist = (distX * distX) + (distY * distY);
			radius = enemy->GetRadius() + player->GetBulletRadius();

			if (dist <= radius * radius) {

				bullet_isHit = true;

			}

			//敵と自機の当たり判定
			player_distX = (float)enemy->GetPosX() - (float)player->GetPosX();
			player_distY = (float)enemy->GetPosY() - (float)player->GetPosY();
			player_dist = (player_distX * player_distX) + (player_distY * player_distY);
			player_radius = enemy->GetRadius() + player->GetRadius();

			if (player_dist <= player_radius * player_radius) {

				player_isHit = true;

			}

			if (bullet_isHit) {

				enemyRespornTimer--;

			}

			if (player_isHit) {

				playerRespornTimer--;

			}

			if (enemyRespornTimer == 0) {

				enemyRespornTimer = 30;

				bullet_isHit = false;

			}

			if (playerRespornTimer == 0) {

				playerRespornTimer = 30;

				player_isHit = false;

			}

			player->Update(keys, preKeys);
			enemy->Update();

			break;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (sceneNum)
		{
		case title:

			Novice::ScreenPrintf(10, 10, "scene=title");

			Novice::ScreenPrintf(10, 30, "Press Enter:play");
		
			break;

		case play:

			if (player_isHit==false) {

				player->Draw();
			
			}

			if (bullet_isHit == false) {

				enemy->Draw();

			}

			Novice::ScreenPrintf(10, 10, "scene=play");

			Novice::ScreenPrintf(10, 30, "Press Enter:title");

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
