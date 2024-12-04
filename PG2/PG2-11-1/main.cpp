#include <Novice.h>
#include "Enemy.h"

const char kWindowTitle[] = "学籍番号";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };

	Enemy* enemyA = new Enemy(100, 300, 4, 0);
	Enemy* enemyB = new Enemy(300, 300, -4, 0);


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
		enemyA->Update();
		enemyB->Update();



		// エネミー同士の当たり判定処理
		float distX = (float)enemyA->GetposX_() - (float)enemyB->GetposX_();
		float distY = (float)enemyA->GetposY_() - (float)enemyB->GetposY_();
		float dist = (distX * distX) + (distY * distY);
		int radius = enemyA->Getradius_() + enemyB->Getradius_();
		if (dist <= radius * radius) {
			enemyA->SetspeedX_(4 * -1);
			enemyA->SetspeedY_(4);
			enemyB->SetspeedX_(-4 * -1);
			enemyB->SetspeedY_(-3);
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		enemyA->Draw();
		enemyB->Draw();

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
