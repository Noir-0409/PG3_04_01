#include <Novice.h>
#include <math.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	int enamyposx = 400;
	int enamyposy = 400;
	int playerposx = 100;
	int playerposy = 100;
	int speed = 7;
	int playercolor = 0;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		float a =float (enamyposx) - (playerposx);
		float b =float (enamyposy) - (playerposy);
		float c = sqrtf(a * a + b * b);

		if (c <= 150.0f) {
			playercolor=BLUE;
		}
		else if (c >= 150.0f) {
			playercolor=RED;
		}


		///
		/// ↓更新処理ここから
		///
		Novice::GetHitKeyStateAll(keys);
		if (keys[DIK_UP]) {
			playerposy= playerposy + -speed;
		}
		if (keys[DIK_DOWN]) {
			playerposy = playerposy + speed;
		}
		if (keys[DIK_RIGHT]) {
			playerposx = playerposx + speed;
		}
		if (keys[DIK_LEFT]){
			playerposx = playerposx + -speed; 
			}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse(enamyposx, enamyposy, 100, 100, 0.0f, 0xFFFFFFFF, kFillModeSolid);
		Novice::DrawEllipse(playerposx, playerposy, 50, 50, 0.0f, playercolor, kFillModeSolid);
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
