#include <Novice.h>

const char kWindowTitle[] = "TR1-2";

enum scene {

	one,
	two

};

struct Vector2 {

	float x;
	float y;

};

struct Player {

	Vector2 position;
	Vector2 verocity;
	float radius;

};

struct Light {

	Vector2 position;
	Vector2 left;
	Vector2 right;
	Vector2 center;
	float velocity;

};

Player player{

	{50,600},
	{10,7},
	25.0f

};

Light light{

	{640,0},
	{0,625},
	{0,625},
	{640,600},
	7.0f

};

int inSerchSpace = false;
int inLight = false;

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

		light.left.x = light.center.x - 50;
		light.right.x = light.center.x + 50;

		if (player.position.x >= 200 && player.position.x <= 1080) {

			inSerchSpace = true;

		} else {

			inSerchSpace = false;

		}

		if (keys[DIK_A]) {

			player.position.x -= player.verocity.x;

		}

		if (keys[DIK_D]) {

			player.position.x += player.verocity.x;

		}

		if (keys[DIK_LEFT]) {

			player.position.x -= player.verocity.x;

		}

		if (keys[DIK_RIGHT]) {

			player.position.x += player.verocity.x;

		}

		if (light.center.x >= 1030) {

			light.velocity = -7.0f;

		} else if (light.center.x <= 250) {

			light.velocity = 7.0f;

		}

		if (inSerchSpace) {

			if (player.position.x >= light.left.x + 40 && player.position.x <= light.right.x - 40) {

				inLight = true;

			}

		}

		if (inLight) {

			light.center.x = player.position.x;

		}
		
		if(inSerchSpace==false){

			inLight = false;
		
		}

		if (inLight == false) {

			light.center.x += light.velocity;

		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawLine(200, 0, 200, 625, BLACK);

		Novice::DrawLine(1080, 0, 1080, 625, BLACK);

		Novice::DrawEllipse((int)player.position.x, (int)player.position.y, (int)player.radius, (int)player.radius, 0.0f, 0x0000ffff,kFillModeSolid);

		Novice::DrawTriangle((int)light.position.x, (int)light.position.y, (int)light.left.x, (int)light.left.y, (int)light.right.x, (int)light.right.y, 0xffffff50, kFillModeSolid);

		Novice::DrawBox(0, 625, 1280, 625, 0.0f,BLACK,kFillModeSolid);

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
