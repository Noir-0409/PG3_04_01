#include <Novice.h>
#include<Vector2.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	

	float wcsY = 500.0f;
	float scsX = 0.0f;
	float scsY = 0.0f;

	struct Ball {
		Vector2 pos;
		Vector2 vel;
		Vector2 acc;
		float radius;
		unsigned int color;
	};

	Ball ball{
		{600,50},{0,0},{0,-0.8f},50,WHITE
	};



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
		/// 
		if (keys[DIK_SPACE] != 0&&preKeys[DIK_SPACE]==0) {
			ball.vel.y = 20.0f;
		}

		ball.vel.x += ball.acc.x;
		ball.vel.y += ball.acc.y;

		ball.pos.x += ball.vel.x;
		ball.pos.y += ball.vel.y;

		if (ball.pos.y <= ball.radius) {
			ball.pos.y = ball.radius;
		}


		scsY = ball.pos.y;

		scsX = ball.pos.x;

		scsY += -wcsY;

		scsY *= -1;

		

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse((int)scsX, (int)scsY,(int)ball.radius,(int)ball.radius, 0.0f, WHITE, kFillModeSolid);

		Novice::DrawLine(0, (int)wcsY, 1280, (int)wcsY, WHITE);

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
