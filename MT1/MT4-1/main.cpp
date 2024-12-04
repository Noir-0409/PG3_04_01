#include <Novice.h>
#define _USE_MATH_DEFINES
#include<math.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	float posX = 400;
	float posY = 400;
	float speed = 10.0f;
	float theta = (1.0f / 2.0f) * float(M_PI);
	float moveX = cosf(theta);
	float moveY = sinf(theta);
	float rad = 100;
	

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

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
		if (Novice::CheckHitKey(DIK_RIGHT)) {
			theta = (1.0f / 4.0f);
			posX = moveX + speed;
		}
		if (Novice::CheckHitKey(DIK_LEFT)) {
			theta = (3.0f / 4.0f);
			posX = moveX - speed;
		}
		if (Novice::CheckHitKey(DIK_UP)) {
			theta = (5.0f / 4.0f);
			posY = moveY - speed;
		}
		if (Novice::CheckHitKey(DIK_DOWN)) {
			theta = (7.0f / 4.0f);
		    posY = moveY + speed;
		}
		if (Novice::CheckHitKey(DIK_RIGHT)&&Novice::CheckHitKey(DIK_DOWN)){
			posX += moveX * rad;
			posY -= moveY * rad;
		}
		if (Novice::CheckHitKey(DIK_RIGHT) && Novice::CheckHitKey(DIK_UP)) {
			posX += moveX * rad;
			posY += moveY * rad;
			}
		if (Novice::CheckHitKey(DIK_LEFT) && Novice::CheckHitKey(DIK_DOWN)) {
			posX -= moveX * rad;
			posY -= moveY * rad;
            }
		if (Novice::CheckHitKey(DIK_LEFT) && Novice::CheckHitKey(DIK_UP)) {
			posX -= moveX * rad;
			posY += moveX * rad;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawBox(posX, (int)posY, 100, 100, 0.0f, 0xFFFFFFFF, kFillModeSolid);
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
