#include <Novice.h>
#include <stdio.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include<assert.h>
const char kWindowTitle[] = "MT2-2";

struct Matrix3x3 {
	float m[3][3];
};
struct Matrix2x2 {

	float m[2][2];
};

struct Vector2 {
	float x;
	float y;
};
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
	Matrix2x2 ans;
	ans.m[0][0] = (matrix1.m[0][0] * matrix2.m[0][0]) + (matrix1.m[0][1] * matrix2.m[1][0]);
	ans.m[1][0] = (matrix1.m[1][0] * matrix2.m[0][0]) + (matrix1.m[1][1] * matrix2.m[1][0]);
	ans.m[0][1] = (matrix1.m[0][0] * matrix2.m[0][1]) + (matrix1.m[0][1] * matrix2.m[1][1]);
	ans.m[1][1] = (matrix1.m[1][0] * matrix2.m[0][1]) + (matrix1.m[1][1] * matrix2.m[1][1]);
	return ans;
}
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix) {
	Vector2 ans;
	ans.x = (vector.x * matrix.m[0][0]) + (vector.y * matrix.m[1][0]);
	ans.y = (vector.x * matrix.m[0][1]) + (vector.y * matrix.m[1][1]);

	return ans;
}
Matrix3x3 MakeTranslateMatrix(Vector2 translate) {
	Matrix3x3 ans;
	ans.m[0][0] = 1.0f;
	ans.m[1][0] = 0.0f;
	ans.m[2][0] = translate.x;
	ans.m[0][1] = 0.0f;
	ans.m[0][2] = 0.0f;
	ans.m[1][1] = 1.0f;
	ans.m[1][2] = 0.0f;
	ans.m[2][1] = translate.y;
	ans.m[2][2] = 1.0f;
	return ans;
}

Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + 1.0f * matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + 1.0f * matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + 1.0f * matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

static const int kRowHeight = 20;
static const int kColumnWidth = 44;

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(
				x + column * kColumnWidth, y + row *
				kRowHeight, "%.02f", matrix.m[row][column]);

		}
	}
}
void VectorScreenPrintf(int x, int y, Vector2 vector) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f",
		vector.y);
}
Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 ans;
	ans.m[0][0] = cosf(theta);
	ans.m[1][0] = sinf(theta);
	ans.m[0][1] = -sinf(theta);
	ans.m[1][1] = cosf(theta);
	return ans;

}

Vector2 LT;//左上
Vector2 RT;//右上
Vector2 LB;//左下
Vector2 RB;//右下
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Vector2 position = { 0.0f,0.0f };
	float width = 200, height = 100;
	Vector2 screen;
	screen.x = 0;
	screen.y = -500;
	//int isspace = 0;
	//float theta = 0;
	float speed = 20;
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);
	int grHandle = Novice::LoadTexture("white1x1.png");
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
		LT.x = -width / 2.0f;
		LT.y = -height / 2.0f;

		LB.x = -width / 2.0f;
		LB.y = +height / 2.0f;

		RT.x = +width / 2.0f;
		RT.y = -height / 2.0f;

		RB.x = +width / 2.0f;
		RB.y = +height / 2.0f;
		if (keys[DIK_W]) {
			position.y += speed;
		}
		if (keys[DIK_S]) {
			position.y -= speed;
		}
		if (keys[DIK_A]) {
			position.x -= speed;
		}
		if (keys[DIK_D]) {
			position.x += speed;
		}
		Matrix3x3 translateMatrix = MakeTranslateMatrix(position);
		Vector2 translateLT = Transform(LT, translateMatrix);
		Vector2 translateLB = Transform(LB, translateMatrix);
		Vector2 translateRT = Transform(RT, translateMatrix);
		Vector2 translateRB = Transform(RB, translateMatrix);
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawQuad(
			int(translateLT.x), int(translateLT.y + screen.y) * (-1),
			int(translateRT.x), int(translateRT.y + screen.y) * (-1),
			int(translateLB.x), int(translateLB.y + screen.y) * (-1),
			int(translateRB.x), int(translateRB.y + screen.y) * (-1),
			0, 0, int(width), int(height), grHandle, WHITE);
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