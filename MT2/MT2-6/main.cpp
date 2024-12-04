#include <Novice.h>

const char kWindowTitle[] = "MT2-6";


struct Vector2 {
	float x;
	float y;
};


// 2x2の行列の作成関数
struct Matrix2x2 {
	float m[2][2];
};

// 3x3の行列の作成関数
struct Matrix3x3 {
	float m[3][3];
};



static const int kRowHeight = 20;
static const int kColumnWidth = 44;



void MatrixScreenPrintf(int x, int y, Matrix2x2 matrix) {
	for (int row = 0; row < 2; ++row) {
		for (int column = 0; column < 2; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}

void VectorScreenPrintf(int x, int y, Vector2 vector) {
	Novice::ScreenPrintf(x, y, "%.02f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector.y);
}



void MatrixScreenPrintf(int x, int y, Matrix3x3 matrix) {
	for (int row = 0; row < 3; ++row) {
		for (int column = 0; column < 3; ++column) {
			Novice::ScreenPrintf(x + column * kColumnWidth, y + row * kRowHeight, "%.02f", matrix.m[row][column]);
		}
	}
}









Matrix2x2 Transpose(Matrix2x2 matrix2) {
	Matrix2x2 matrix;
	matrix = matrix2;
	float trans = 0;
	trans = matrix.m[0][1];
	matrix.m[0][1] = matrix.m[1][0];
	matrix.m[1][0] = trans;
	return matrix;
}
Matrix3x3 Transpose(Matrix3x3 matrix2) {
	float trans = 0;
	Matrix3x3 matrix;
	matrix = matrix2;

	trans = matrix.m[0][1];
	matrix.m[0][1] = matrix.m[1][0];
	matrix.m[1][0] = trans;
	trans = matrix.m[0][2];
	matrix.m[0][2] = matrix.m[2][0];
	matrix.m[2][0] = trans;
	trans = matrix.m[1][2];
	matrix.m[1][2] = matrix.m[2][1];
	matrix.m[2][1] = trans;
	return matrix;
}




// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	// キー入力結果を受け取る箱
	char keys[256] = { 0 };
	char preKeys[256] = { 0 };



	Matrix2x2 m1;
	m1.m[0][0] = 1.0f; m1.m[0][1] = 2.0f;
	m1.m[1][0] = 3.0f; m1.m[1][1] = 4.0f;

	Matrix3x3 m2;
	m2.m[0][0] = 1.0f; m2.m[0][1] = 2.0f; m2.m[0][2] = 0.0f;
	m2.m[1][0] = 3.0f; m2.m[1][1] = 4.0f; m2.m[1][2] = 0.0f;
	m2.m[2][0] = 5.0f; m2.m[2][1] = 6.0f; m2.m[2][2] = 1.0f;


	Matrix2x2 inverseM1 = Transpose(m1);
	Matrix3x3 inverseM2 = Transpose(m2);



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



		MatrixScreenPrintf(0, kRowHeight * 0, inverseM1);
		MatrixScreenPrintf(0, kRowHeight * 4 + 10, inverseM2);



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
