#include <Novice.h>

const char kWindowTitle[] = "AL2-1-2";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 700, 700);

	//　変数宣言
	int size_map_x = 28; //マップチップXサイズ
	int size_map_y = 28; //マップチップYサイズ

	int num_map_y = 25; //28*25
	int num_map_x = 25; //28*25

	int map[25][25] = {

		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,

		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,

		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,

		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,

		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1, 0,1,0,1,0, 1,0,1,0,1,
		1,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,1,
		1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1, 1,1,1,1,1,

	}; // マップの構造

	//　プレイヤーの情報
	float playerPosX = 28.0f;
	float playerPosY = 28.0f;
	float playerRadius = 14.0f;
	float playerSpeed = 28.0f;

	// 壁がある方向に動けなくする変数
	float oldPlayerPosX = 0.0f;
	float oldPlayerPosY = 0.0f;

	// プレイヤーの座標を割り出す変数
	float tempPlayerPosX = 0.0f;
	float tempPlayerPosY = 0.0f;

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

		// プレイヤーの仮座標
		oldPlayerPosX = playerPosX;
		oldPlayerPosY = playerPosY;

		// プレイヤーの移動処理

		// 上方向への移動
		if (keys[DIK_W]&&preKeys[DIK_W]==false) {

			playerPosY -= playerSpeed;

		}

		// 下方向への移動
		if (keys[DIK_S]&&preKeys[DIK_S]==false) {

			playerPosY += playerSpeed;

		}

		// 左方向への移動
		if (keys[DIK_A]&&preKeys[DIK_A]==false) {

			playerPosX -= playerSpeed;

		}

		// 右方向への移動
		if (keys[DIK_D]&&preKeys[DIK_D]==false) {

			playerPosX += playerSpeed;

		}

		// プレイヤーの現在の座標を割り出す
		tempPlayerPosX = playerPosX / size_map_x;
		tempPlayerPosY = playerPosY / size_map_y;

		// プレイヤーと壁の当たり判定
		if (map[(int)tempPlayerPosY][(int)tempPlayerPosX] == 1) {

			playerPosX = oldPlayerPosX;

			playerPosY = oldPlayerPosY;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		
		// 背景の描画
		Novice::DrawBox(0, 0, 700, 700, 0.0f, 0x000000FF, kFillModeSolid);

		// マップの描画
		for (int y = 0; y < num_map_y; y++) {

			for (int x = 0; x < num_map_x; x++) {

				if (map[y][x] == 1) {

					Novice::DrawBox(x * size_map_y, y * size_map_x, size_map_y, size_map_x, 0.0f, 0x808080FF, kFillModeSolid);

				}
			}
		}

		// プレイヤーの描画
		Novice::DrawBox((int)playerPosX, (int)playerPosY, (int)playerRadius * 2, (int)playerRadius * 2, 0.0f, RED, kFillModeSolid);

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
