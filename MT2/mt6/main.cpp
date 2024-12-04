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

//2x2の逆行列
Matrix2x2 Inverse(Matrix2x2 matrix) {
	Matrix2x2 result;
	float determinant = matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0];

	// 行列が逆行列を持つことを確認します
	if (determinant != 0.0) {
		float invDeterminant = (float)1.0 / (float)determinant;
		result.m[0][0] = matrix.m[1][1] * invDeterminant;
		result.m[0][1] = -matrix.m[0][1] * invDeterminant;
		result.m[1][0] = -matrix.m[1][0] * invDeterminant;
		result.m[1][1] = matrix.m[0][0] * invDeterminant;
	} else {
		
		for (int i = 0; i < 2; ++i) {
			for (int j = 0; j < 2; ++j) {
				result.m[i][j] = 0.0f;
			}
		}
	}

	return result;
}

//3x3の逆行列
Matrix3x3 Inverse(Matrix3x3 matrix) {
	Matrix3x3 result;
	// 行列式を計算
	float determinant =
		matrix.m[0][0] * (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) -
		matrix.m[0][1] * (matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) +
		matrix.m[0][2] * (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]);

	// 行列が逆行列を持つことを確認します
	if (determinant != 0.0) {
		float invDeterminant = 1.0f / determinant;
		result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) * invDeterminant;
		result.m[0][1] = (matrix.m[0][2] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][2]) * invDeterminant;
		result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) * invDeterminant;
		result.m[1][0] = (matrix.m[1][2] * matrix.m[2][0] - matrix.m[1][0] * matrix.m[2][2]) * invDeterminant;
		result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) * invDeterminant;
		result.m[1][2] = (matrix.m[0][2] * matrix.m[1][0] - matrix.m[0][0] * matrix.m[1][2]) * invDeterminant;
		result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) * invDeterminant;
		result.m[2][1] = (matrix.m[0][1] * matrix.m[2][0] - matrix.m[0][0] * matrix.m[2][1]) * invDeterminant;
		result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) * invDeterminant;
	} else {
		// 逆行列が存在しない場合は、すべての要素をゼロに設定します
		for (int i = 0; i < 3; ++i) {
			for (int j = 0; j < 3; ++j) {
				result.m[i][j] = 0.0f;
			}
		}
	}

	return result;
}


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

		Matrix2x2 m1;
		m1.m[0][0] = 1.0f;
		m1.m[0][1] = 2.0f;
		m1.m[1][0] = 3.0f;
		m1.m[1][1] = 4.0f;

		Matrix3x3 m2;
		m2.m[0][0] = 1.0f;
		m2.m[0][1] = 2.0f;
		m2.m[0][2] = 0.0f;
		m2.m[1][0] = 3.0f;
		m2.m[1][1] = 4.0f;
		m2.m[1][2] = 0.0f;
		m2.m[2][0] = 5.0f;
		m2.m[2][1] = 6.0f;
		m2.m[2][2] = 1.0f;

		Matrix2x2 inverseM1 = Inverse(m1);
		Matrix3x3 inverseM2 = Inverse(m2);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, kRowHeight * 0, inverseM1);

		MatrixScreenPrintf(0, kRowHeight * 2 + 10, inverseM2);

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
