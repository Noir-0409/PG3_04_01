#include <Novice.h>
#include <stdio.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
const char kWindowTitle[] = "MT2-1";
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

Vector2 LT;
Vector2 RT;
Vector2 LB;
Vector2 RB;
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	/*float kLeftTopX = 0, kLeftTopY = 0, kLeftBottomX = 0, kLeftBottomY = 0;
	float kRightTopX = 0, kRightTopY = 0, kRightBottomX = 0, kRightBottomY = 0;
	float theta = 0;
	float width = 200, height = 100;
	int isspace = 0;
	float positionX = 400, positionY = 400;
	float leftToppositionX = 0, leftToppositionY = 0, leftBottompositionX = 0, leftBottompositionY = 0;
	float RightToppositionX = 0, RightToppositionY = 0, RightBottompositionX = 0, RightBottompositionY = 0;
	*/
	float width = 200, height = 100;
	Vector2 screen;
	screen.x = 0;
	screen.y = -500;
	int isspace = 0;
	float theta = 0;
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
		if (keys[DIK_SPACE]) {
			isspace = 1;
		}
		if (isspace == 1) {
			theta += 1.0f / 8.0f * float(M_PI);
		} else
			theta = 1.0f / 8.0f * float(M_PI);
		Matrix2x2 rotateMatrix = MakeRotateMatrix(theta);
		Vector2 rotatedLT = Multiply(LT, rotateMatrix);
		LT.x = rotatedLT.x + 400.0f;
		LT.y = rotatedLT.y + 100.0f;
		Vector2 rotatedRT = Multiply(RT, rotateMatrix);
		RT.x = rotatedRT.x + 400.0f;
		RT.y = rotatedRT.y + 100.0f;
		Vector2 rotatedLB = Multiply(LB, rotateMatrix);
		LB.x = rotatedLB.x + 400.0f;
		LB.y = rotatedLB.y + 100.0f;
		Vector2 rotatedRB = Multiply(RB, rotateMatrix);
		RB.x = rotatedRB.x + 400.0f;
		RB.y = rotatedRB.y + 100.0f;
		
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawQuad(
			int(LT.x), int(LT.y + screen.y) * (-1),
			int(RT.x), int(RT.y + screen.y) * (-1),
			int(LB.x), int(LB.y + screen.y) * (-1),
			int(RB.x), int(RB.y + screen.y) * (-1),
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
