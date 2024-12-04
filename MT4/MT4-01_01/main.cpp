#include <Novice.h>
#include <cmath>

const char kWindowTitle[] = "MT4-01_01";

struct Matrix4x4 {
	float m[4][4];
};

struct Vector3 {
	float x;
	float y;
	float z;
};

Vector3 Normalize(const Vector3& v) {
	float length = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	return { v.x / length, v.y / length, v.z / length };
}

Matrix4x4 MakeRotateAxisAngle(const Vector3& axis, float angle) {

	Matrix4x4 result;

	// 回転軸を正規化
	Vector3 normAxis = Normalize(axis);
	float x = normAxis.x;
	float y = normAxis.y;
	float z = normAxis.z;

	float cosTheta = std::cos(angle);
	float sinTheta = std::sin(angle);
	float oneMinusCos = 1.0f - cosTheta;

	// 回転行列の各要素を計算
	result.m[0][0] = cosTheta + x * x * oneMinusCos;
	result.m[0][1] = x * y * oneMinusCos - z * sinTheta;
	result.m[0][2] = x * z * oneMinusCos + y * sinTheta;
	result.m[0][3] = 0.0f;

	result.m[1][0] = y * x * oneMinusCos + z * sinTheta;
	result.m[1][1] = cosTheta + y * y * oneMinusCos;
	result.m[1][2] = y * z * oneMinusCos - x * sinTheta;
	result.m[1][3] = 0.0f;

	result.m[2][0] = z * x * oneMinusCos - y * sinTheta;
	result.m[2][1] = z * y * oneMinusCos + x * sinTheta;
	result.m[2][2] = cosTheta + z * z * oneMinusCos;
	result.m[2][3] = 0.0f;

	result.m[3][0] = 0.0f;
	result.m[3][1] = 0.0f;
	result.m[3][2] = 0.0f;
	result.m[3][3] = 1.0f;

	return result;

}

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {
	// ラベルの表示
	Novice::ScreenPrintf(x, y, "%s", label);

	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + row * kColumnWidth, y + column * kRowHeight + 20, "%6.02f", matrix.m[column][row]);
		}
	}
}

Vector3 axis = Normalize({ 1.0f,1.0f,1.0f });
float angle = 0.44f;
Matrix4x4 rotateMatrix = MakeRotateAxisAngle(axis, angle);

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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		MatrixScreenPrintf(0, 0, rotateMatrix, "rotateMatrix");

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
