#include <Novice.h>

typedef struct Vector2 {
	float x;
	float y;
}Vector2;

struct Player {
	Vector2 pos;
	Vector2 speed;
	float radius;
	unsigned int color;
};

Player player = {
		{640.0f,360.0f}, //pos
		{0.0f,0.0f},     //speed
		30.0f,           //radius
		WHITE             //color
};

void playerMove( char* keys) {

	if (keys[DIK_A]) {

		player.pos.x -= player.speed.x;

	}

	if (keys[DIK_D]) {

		player.pos.x += player.speed.x;

	}

	if (keys[DIK_W]) {

		player.pos.y -= player.speed.y;

	}

	if (keys[DIK_S]) {

		player.pos.y += player.speed.y;

	}
}

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

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

		playerMove(keys);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse((int)player.pos.x, (int)player.pos.y,
			(int)player.radius, (int)player.radius,
			0.0f, player.color, kFillModeSolid);

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
