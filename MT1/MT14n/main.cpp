#include <Novice.h>
#define _USE_MATH_DEFINES
#include <Math.h>
#include <Vector2.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

float length(Vector2 ba) {

	return sqrtf(ba.x * ba.x + ba.y * ba.y);

}

Vector2 normalize(Vector2 ba) {

	float length1 = length(ba);

	if (length1 != 0.0f) {
		Vector2(ba.x / length1, ba.y / length1);
	} else {
		return Vector2(0.0f, 0.0f);
	}
}

float dot(Vector2 d, Vector2 e) {
	return d.x * e.x + d.y * e.y;
}

int clamp(int num, int min, int max) {

	if (num > max) {

		return max;

	} else if (num < min) {

		return min;

	} else {

		return num;

	}

}

struct  Vector2 {
	float x;
	float y;
};
struct Ball {
	Vector2 pos;
	Vector2 velosity;
	Vector2 accelaration;
	float radius;
	unsigned int color;
};
struct Vector2 WCS {
	0,
		500
};

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	Ball a;
	a.pos.x = 100;
	a.pos.y = 100;
	a.radius = 60.0f;

	Ball b;
	b.pos.x = 1000;
	b.pos.y = 400;
	b.radius = 60.0f;

	Ball player;
	player.pos.x = 300;
	player.pos.y = 300;
	player.velosity.x = 5;
	player.velosity.y = 5;
	player.radius = 30;
	player.color = WHITE;




	Vector2 d;

	Vector2 ba;

	Vector2 e;
	Vector2 f;
	float  t = 0;
	float distance;

	Vector2 w;

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

		if (keys[DIK_A]) {
			player.pos.x -= player.velosity.x;
		}

		if (keys[DIK_D]) {
			player.pos.x += player.velosity.x;
		}

		if (keys[DIK_W]) {
			player.pos.y -= player.velosity.y;
		}

		if (keys[DIK_S]) {
			player.pos.y += player.velosity.y;
		}

		d.x = player.pos.x - a.pos.x;
		d.y = player.pos.y - a.pos.y;

		ba.x = b.pos.x - a.pos.x;
		ba.y = b.pos.y - a.pos.y;

		e = normalize(ba);

		t = dot(d, e) / length(ba);

		t = clamp(t, 1, 0);

		f.x = (1.0f - t) * a.pos.x + t * b.pos.x;
		f.y = (1.0f - t) * a.pos.y + t * b.pos.y;


		w.x = player.pos.x - f.x;
		w.y = player.pos.y - f.y;

		distance = length((Vector2)w);




		if (distance < a.radius + b.radius) {
			//カプセルの中に入ってるとき
			player.color = BLUE;
		} else {
			if (distance > a.radius + b.radius) {
				//カプセルの中に入っないとき
				player.color = WHITE;
			}
		}

		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawEllipse(static_cast<int>(a.pos.x), static_cast<int>(a.pos.y - WCS.y) * -1, static_cast<int>(a.radius), static_cast<int>(a.radius), 0.0f, WHITE, kFillModeSolid);
		Novice::DrawEllipse(static_cast<int>(b.pos.x), static_cast<int>(b.pos.y - WCS.y) * -1, static_cast<int>(b.radius), static_cast<int>(b.radius), 0.0f, WHITE, kFillModeSolid);

		Novice::DrawLine(static_cast<int>(a.pos.x), static_cast<int>(a.pos.y - WCS.y) * -1, static_cast<int>(b.pos.x), static_cast<int>(b.pos.y - WCS.y) * -1, WHITE);
		Novice::DrawEllipse(static_cast<int>(player.pos.x), static_cast<int>(player.pos.y - WCS.y) * -1, static_cast<int>(player.radius), static_cast<int>(player.radius), 0.0f, static_cast<int>(player.color), kFillModeSolid);
		

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
