#include <Novice.h>
#define USE_MATH_DEFINE
#include<math.h>

const char kWindowTitle[] = "MT9_00";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	struct vector {
		float posX;
		float posY;
	};
	struct cicle {
		vector center;
		float radius;
		vector speed;
	};

	float speed = 20.0f;


	float length = 0.0f;

	int playerColer = RED;

	struct vector playerPos = {
		0.0f,
		0.0f
	};
	struct vector enemyPos = {
		400,400
	};


	struct cicle player = {
	{ playerPos.posX, playerPos.posY },
	50.0f
	};
	struct cicle enemy = {
		{ 400.0f, 400.0f },
		100.0f
	};

	float a = enemyPos.posX - playerPos.posX;
	float b = enemyPos.posY - playerPos.posY;
	float c = sqrtf(a * a + b * b);

	playerPos.posX = 100.0f;
	playerPos.posY = 100.0f;
	enemyPos.posX = 400.0f;
	enemyPos.posY = 400.0f;
	player.radius = 50.0f;
	enemy.radius = 100.0f;

	bool isPlayerAlive = false;
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

		///
		/// ↓更新処理ここから
		///
		/// 


		player.speed.posX = float(Novice::CheckHitKey(DIK_D) - Novice::CheckHitKey(DIK_A));
		player.speed.posY = float(Novice::CheckHitKey(DIK_S) - Novice::CheckHitKey(DIK_W));



		length = sqrtf(player.speed.posX * player.speed.posX + player.speed.posY * player.speed.posY);

		if (length != 0.0f) {

			player.speed.posX = player.speed.posX / length;
			player.speed.posY = player.speed.posY / length;

			player.speed.posX *= speed;
			player.speed.posY *= speed;
		}


		playerPos.posX += player.speed.posX;
		playerPos.posY += player.speed.posY;



		a = enemyPos.posX - playerPos.posX;
		b = enemyPos.posY - playerPos.posY;
		c = sqrtf((a * a) + (b * b));

		if (c <= player.radius + enemy.radius) {
			playerColer = 0x0000FFFF;
			isPlayerAlive = true;
		} else {
			playerColer = RED;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse((int)enemyPos.posX, (int)enemyPos.posY,
			(int)enemy.radius, (int)enemy.radius, 0.0f, WHITE, kFillModeSolid);


		Novice::DrawEllipse((int)(playerPos.posX), (int)(playerPos.posY),
			(int)player.radius, (int)player.radius, 0.0f, playerColer, kFillModeSolid);

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
