#include <Novice.h>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//シーン列挙型
	enum scene {

		title,
		play

	};

	int sceneNum = title;

	Player* player = new Player();
	Enemy* enemy = new Enemy();
	Bullet* bullet = new Bullet();

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

		switch (sceneNum) {

		case title:

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

				sceneNum = play;

			}

			break;

		case play:

			if (keys[DIK_RETURN] && preKeys[DIK_RETURN] == false) {

				sceneNum = title;

			}

			// 初期化処理
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

		switch (sceneNum) {

		case title:

			Novice::ScreenPrintf(10, 10, "title");

			Novice::ScreenPrintf(10, 30, "Press Enter:Play");

			break;

		case play:

			player->Draw();

			enemy->Draw();

			bullet->Draw();


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
