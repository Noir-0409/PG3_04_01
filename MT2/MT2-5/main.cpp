#include <Novice.h>
#include <stdio.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include<assert.h>
const char kWindowTitle[] = "MT2-5";
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
/*Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2) {
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
}*/
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

Matrix3x3 MakeScaleMatrix(Vector2 scale) {
	Matrix3x3 ans;
	ans.m[0][0] = scale.x;
	ans.m[1][0] = 0.0f;
	ans.m[2][0] = 0.0f;
	ans.m[0][1] = 0.0f;
	ans.m[0][2] = 0.0f;
	ans.m[1][1] = scale.y;
	ans.m[1][2] = 0.0f;
	ans.m[2][1] = 0.0f;
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

Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 ans;
	ans.m[0][0] = (matrix1.m[0][0] * matrix2.m[0][0]) + (matrix1.m[0][1] * matrix2.m[1][0]) + (matrix1.m[0][2] * matrix2.m[2][0]);
	ans.m[1][0] = (matrix1.m[1][0] * matrix2.m[0][0]) + (matrix1.m[1][1] * matrix2.m[1][0]) + (matrix1.m[1][2] * matrix2.m[2][0]);
	ans.m[2][0] = (matrix1.m[2][0] * matrix2.m[0][0]) + (matrix1.m[2][1] * matrix2.m[1][0]) + (matrix1.m[2][2] * matrix2.m[2][0]);
	ans.m[0][1] = (matrix1.m[0][0] * matrix2.m[0][1]) + (matrix1.m[0][1] * matrix2.m[1][1]) + (matrix1.m[0][2] * matrix2.m[2][1]);
	ans.m[1][1] = (matrix1.m[1][0] * matrix2.m[0][1]) + (matrix1.m[1][1] * matrix2.m[1][1]) + (matrix1.m[1][2] * matrix2.m[2][1]);
	ans.m[2][1] = (matrix1.m[2][0] * matrix2.m[0][1]) + (matrix1.m[2][1] * matrix2.m[1][1]) + (matrix1.m[2][2] * matrix2.m[2][1]);
	ans.m[0][2] = (matrix1.m[0][0] * matrix2.m[0][2]) + (matrix1.m[0][1] * matrix2.m[1][2]) + (matrix1.m[0][2] * matrix2.m[2][2]);
	ans.m[1][2] = (matrix1.m[1][0] * matrix2.m[0][2]) + (matrix1.m[1][1] * matrix2.m[1][2]) + (matrix1.m[1][2] * matrix2.m[2][2]);
	ans.m[2][2] = (matrix1.m[2][0] * matrix2.m[0][2]) + (matrix1.m[2][1] * matrix2.m[1][2]) + (matrix1.m[2][2] * matrix2.m[2][2]);
	return ans;
}
Matrix3x3 MakeRotateMatrix(float theta) {
	Matrix3x3 ans;
	ans.m[0][0] = cosf(theta);
	ans.m[1][0] = -sinf(theta);
	ans.m[2][0] = 0;
	ans.m[0][1] = sinf(theta);
	ans.m[1][1] = cosf(theta);
	ans.m[2][1] = 0;
	ans.m[0][2] = 0;
	ans.m[1][2] = 0;
	ans.m[2][2] = 1;
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
/*Matrix2x2 MakeRotateMatrix(float theta) {
	Matrix2x2 ans;
	ans.m[0][0] = cosf(theta);
	ans.m[1][0] = sinf(theta);
	ans.m[0][1] = -sinf(theta);
	ans.m[1][1] = cosf(theta);
	return ans;

}
*/
Matrix3x3 MakeAfineMatrix(Vector2 scale, float rotate, Vector2 translate) {
	Matrix3x3 ans;
	Matrix3x3 scaleMatrix = MakeScaleMatrix(scale);
	Matrix3x3 rotateMatrix = MakeRotateMatrix(rotate);
	Matrix3x3 translateMatrix = MakeTranslateMatrix(translate);
	Matrix3x3 worldMatrix = Multiply(scaleMatrix, rotateMatrix);
	worldMatrix = Multiply(worldMatrix, translateMatrix);
	ans = worldMatrix;

	return ans;
}
Vector2 LT;//左上
Vector2 RT;//右上
Vector2 LB;//左下
Vector2 RB;//右下
// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {
	Vector2 rectCenter = { 400.0f,100.0f };
	Vector2 scale = { 0.0f,0.0f };
	float s = 0.01f;
	float width = 200, height = 100;
	Vector2 screen;
	screen.x = 0;
	screen.y = -500;
	//int isspace = 0;
	float theta = 0;
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
		scale.x += s;
		scale.y += s;
		if (scale.x >= 1.0f) {
			s = s * (-1.0f);
			//scale.y =scale.y*(-1.0f);
		}
		if (scale.x <= -1.0f) {
			s = s * (-1.0f);
			//scale.y = scale.y * (-1.0f);
		}
		if (keys[DIK_W]) {
			rectCenter.y += speed;
		}
		if (keys[DIK_S]) {
			rectCenter.y -= speed;
		}
		if (keys[DIK_A]) {
			rectCenter.x -= speed;
		}
		if (keys[DIK_D]) {
			rectCenter.x += speed;
		}
		theta += 1.0f / 32.0f * float(M_PI);
		//Matrix3x3 worldMatrix = MakeAfineMatrix(scale, theta, rectCenter);
		Matrix3x3 rotateMatrix = MakeRotateMatrix(theta);
		Matrix3x3 translateMatrix = MakeTranslateMatrix(rectCenter);
		Matrix3x3 worldMatrix = Multiply(rotateMatrix, translateMatrix);
		Vector2 worldLT = Transform(LT, worldMatrix);
		Vector2 worldLB = Transform(LB, worldMatrix);
		Vector2 worldRT = Transform(RT, worldMatrix);
		Vector2 worldRB = Transform(RB, worldMatrix);
		/*Matrix3x3 scaleMatrix = MakeScaleMatrix(scale);
		Matrix3x3 rotateMatrix = MakeRotateMatrix(theta);
		Matrix3x3 translateMatrix = MakeTranslateMatrix(rectCenter);
		Matrix3x3 worldMatrix = Multiply(scaleMatrix, rotateMatrix);
		worldMatrix = Multiply(worldMatrix, translateMatrix);
		Vector2 worldLT = Transform(LT, worldMatrix);
		Vector2 worldLB = Transform(LB, worldMatrix);
		Vector2 worldRT = Transform(RT, worldMatrix);
		Vector2 worldRB = Transform(RB, worldMatrix);
		*/
		/*
		Matrix3x3 rotateMatrix = MakeRotateMatrix(theta);
		Matrix3x3 translateMatrix = MakeTranslateMatrix(rectCenter);
		Matrix3x3 worldMatrix = Multiply(rotateMatrix, translateMatrix);
		Vector2 worldLT = Transform(LT, worldMatrix);
		Vector2 worldLB = Transform(LB, worldMatrix);
		Vector2 worldRT = Transform(RT, worldMatrix);
		Vector2 worldRB = Transform(RB, worldMatrix);
		*/
		/*Matrix3x3 translateMatrix = MakeTranslateMatrix(position);
		Vector2 translateLT = Transform(LT, translateMatrix);
		Vector2 translateLB = Transform(LB, translateMatrix);
		Vector2 translateRT = Transform(RT, translateMatrix);
		Vector2 translateRB = Transform(RB, translateMatrix);
		*/
		/*if (isspace == 1) {
			theta -= 1.0f / 8.0f * float(M_PI);
		}
		else
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
		*/
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawQuad(
			int(worldLT.x), int(worldLT.y + screen.y) * (-1),
			int(worldRT.x), int(worldRT.y + screen.y) * (-1),
			int(worldLB.x), int(worldLB.y + screen.y) * (-1),
			int(worldRB.x), int(worldRB.y + screen.y) * (-1),
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
