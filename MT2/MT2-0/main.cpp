#include <Novice.h>
#include <Vector2.h>

// 2x2の行列
struct Matrix2x2
{

	float m[2][2];

};

// 2次元ベクトル
struct Vector2
{

	float x;
	float y;

};

//struct {
//	double data[2][2];
//} Matrix2x2;

// 行列の加法
Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2) {

	Matrix2x2 result;

	for (int i = 0; i < 1; i++) {

		for (int j = 0; j < 1; j++) {

			result.data[i][j] = matrix1.data[i][j] + matrix2.data[i][j];
		}
	}

	return result;
}

// 行列の減法
Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2) {

	Matrix2x2 result;

	for (int i = 0; i < 1; i++) {

		for (int j = 0; j < 1; j++) {

			result.data[i][j] = matrix1.data[i][j] - matrix2.data[i][j];

		}

	}

	return result;

}

// 行列の積
Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);

// ベクトルと行列の積
Vector2 Multiply(Vector2 vector, Matrix2x2 matrix);

static const int kRowHeight = 20;
static const int kColmunWidth = 44;

void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {

	for (int row; row < 2; ++row) {

		for (int column; column < 2; ++column) {

			Novice::ScreenPrintf(x + column * kColmunWidth, y + row *
				kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, Vector2 vector) {

	Novice::ScreenPrintf(x, y, "%.02", vector.x);

	Novice::ScreenPrintf(x + kColmunWidth, y, "%.02", vector.y);

}

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Matrix2x2 m1;

	m1.m[0][0] = 1.0f;
	m1.m[0][1] = 2.0f;
	m1.m[1][0] = 3.0f;
	m1.m[1][1] = 4.0f;

	Matrix2x2 m2;

	m2.m[0][0] = 5.0f;
	m2.m[0][1] = 6.0f;
	m2.m[1][0] = 7.0f;
	m2.m[1][1] = 8.0f;

	Vector2 v = { 10,20 };

	Matrix2x2 resultAdd = Add(m1, m2);

	Matrix2x2 resultSubtract = Subtract(m1, m2);

	Matrix2x2 resultMultiply = Multiply(m1, m2);

	Vector2 resultVector = Multiply(v, m1);

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

		MatrixScreenPrintf(0, kRowHeight * 0, resultAdd);

		MatrixScreenPrintf(0, kRowHeight * 2 + 10, resultSubtract);

		MatrixScreenPrintf(0, kRowHeight * 4 + 20, resultMultiply);

		VectorScreenPrintf(0, kRowHeight * 6 + 30, resultVector);

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
