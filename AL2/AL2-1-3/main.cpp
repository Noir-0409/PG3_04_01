#include <Novice.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 640, 320);

	int size_map_x = 32; //マップチップxサイズ
	int size_map_y = 32; //マップチップyサイズ

	int num_map_y = 10; //32*10
	int num_map_x = 20; //32*20

	int map[10][20] = {

		0,0,1,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,
		0,0,1,0,1,1,0,1,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,1,0,0,1,0,1,0,0,1,0,0,1,0,0,0,0,0,0,
		0,0,1,1,1,1,0,1,0,1,0,0,1,0,0,1,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,
		0,0,0,0,0,0,0,0,0,0,1,0,0,1,0,0,0,0,0,0,
		0,0,1,1,1,1,1,1,0,1,0,0,1,0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,
		0,0,1,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,0,0,
		0,0,1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,

	};

	//　プレイヤーの情報
	float playerPosX = 32.0f;
	float playerPosY = 32.0f;
	float playerRadius = 32.0f;
	float playerSpeed = 4.0f;

	// プレイヤーの各頂点
	float playerLeftTopX = 0.0f;
	float playerLeftTopY = 0.0f;
	float playerLeftBottomX = 0.0f;
	float playerLeftBottomY = 0.0f;
	float playerRightTopX = 0.0f;
	float playerRightTopY = 0.0f;
	float playerRightBottomX = 0.0f;
	float playerRightBottomY = 0.0f;

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

		// プレイヤーの各頂点の座標
		playerLeftTopX = playerPosX / size_map_x;
		playerLeftTopY = playerPosY / size_map_y;

		playerRightTopX = (playerPosX + playerRadius - 1 ) / size_map_x;
		playerRightTopY = playerPosY / size_map_y;

		playerLeftBottomX = playerPosX / size_map_x;
		playerLeftBottomY = (playerPosY + playerRadius - 1 ) / size_map_y;

		playerRightBottomX = (playerPosX + playerRadius - 1 ) / size_map_x;
		playerRightBottomY = (playerPosY + playerRadius - 1 ) / size_map_y;

		// プレイヤーの移動処理

		// 上方向への移動

		if (keys[DIK_W]) {

			playerLeftTopY = (playerPosY - playerSpeed) / size_map_y;

			playerLeftTopX = playerPosX  / size_map_x;

			playerRightTopY = (playerPosY - playerSpeed) / size_map_y;

			playerRightTopX = (playerPosX + playerRadius-1) / size_map_x;

			if (map[(int)playerLeftTopY][(int)playerLeftTopX] == 0 &&
				map[(int)playerRightTopY][(int)playerRightTopX] == 0) {
		
				playerPosY -= playerSpeed;
			
			}
		}

		// 下方向への移動

		if (keys[DIK_S]) {

			playerLeftBottomY = (playerPosY + playerRadius -1 + playerSpeed) / size_map_y;

			playerLeftBottomX = playerPosX  / size_map_x;

			playerRightBottomY = (playerPosY + playerRadius -1  + playerSpeed) / size_map_y;

			playerRightBottomX = (playerPosX + playerRadius -1 ) / size_map_x;

			if (map[(int)playerLeftBottomY][(int)playerLeftBottomX] == 0 &&
				map[(int)playerRightBottomY][(int)playerRightBottomX] == 0) {

				playerPosY += playerSpeed;

			}
		}

		// 左方向への移動

		if (keys[DIK_A]) {

			playerLeftTopY = playerPosY / size_map_y;

			playerLeftTopX = (playerPosX - playerSpeed) / size_map_x;

			playerLeftBottomY = (playerPosY + playerRadius -1 ) / size_map_y;

			playerLeftBottomX = (playerPosX - playerSpeed) / size_map_x;

			if (map[(int)playerLeftTopY][(int)playerLeftTopX] == 0 &&
				map[(int)playerLeftBottomY][(int)playerLeftBottomX] == 0) {

				playerPosX -= playerSpeed;

			}
		}

		// 右方向への移動

		if (keys[DIK_D]) {

			playerRightTopY = playerPosY / size_map_y;

			playerRightTopX = (playerPosX + playerRadius -1  + playerSpeed) / size_map_x;

			playerRightBottomY = (playerPosY + playerRadius -1 ) / size_map_y;

			playerRightBottomX = (playerPosX + playerRadius -1  + playerSpeed) / size_map_x;

			if (map[(int)playerRightTopY][(int)playerRightTopX] == 0 &&
				map[(int)playerRightBottomY][(int)playerRightBottomX] == 0) {

				playerPosX += playerSpeed;

			}

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		// 背景の描画
		Novice::DrawBox(0, 0, 640, 320, 0.0f, 0x000000FF, kFillModeSolid);

		// マップの描画
		for (int y = 0; y < num_map_y; y++) {

			for (int x = 0; x < num_map_x; x++) {

				if (map[y][x] == 1) {

					Novice::DrawBox(x * size_map_y, y * size_map_x, size_map_y, size_map_x, 0.0f, 0x808080FF, kFillModeSolid);

				}
			}
		}

		// プレイヤーの描画
		Novice::DrawBox((int)playerPosX, (int)playerPosY, (int)playerRadius , (int)playerRadius , 0.0f, RED, kFillModeSolid);

		Novice::ScreenPrintf(0, 0, "leftTop:map[%f][%f]", playerLeftTopY, playerLeftTopX);

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
