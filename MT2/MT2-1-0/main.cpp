#include <Novice.h>
#define _USE_DEFINE_MATH;
#include <math.h>

struct Matrix2x2 {

	float m[2][2];

};

struct Vector2 {

	float x;
	float y;

};

Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 rotationMatrix;

	float cosTheta = cos(theta);
	float sinTheta = sin(theta);

	rotationMatrix.m[0][0] = cosTheta;
	rotationMatrix.m[0][1] = -sinTheta;
	rotationMatrix.m[1][0] = sinTheta;
	rotationMatrix.m[1][1] = cosTheta;

	return rotationMatrix;
}

Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 result;

	result.x = matrix.m[0][0] * vector.x + matrix.m[0][1] * vector.y;
	result.y = matrix.m[1][0] * vector.x + matrix.m[1][1] * vector.y;

	return result;
}

int whiteGH = Novice::LoadTexture("./NoviceResources./white1x1.png");

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	float theta = 45.0f;

	Vector2 leftTop = { 400,100 };
	Vector2 rightTop = { 600,100 };
	Vector2 leftBottom = { 400,200 };
	Vector2 rightBottom = { 600,100 };

	Matrix2x2 rotateMatrix = MakeRotateMatrix(theta);

	Vector2 rotatedLeftTop = Multiply(leftTop, rotateMatrix);

	rotatedLeftTop.x = 400.0f;
	rotatedLeftTop.y = 400.0f;

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
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawQuad((int)leftTop.x, (int)leftTop.y, (int)rightTop.x, (int)rightTop.y, (int)leftBottom.x, (int)leftBottom.y, (int)rightBottom.x, (int)rightBottom.y, 0, 0, 1.0f, 1.0f, whiteGH, WHITE);

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
