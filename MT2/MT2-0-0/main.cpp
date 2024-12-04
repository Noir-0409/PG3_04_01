#include <Novice.h>
#include <Vector2.h>


const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

struct Matrix2x2 {

	float m[2][2];

};

struct Vector2 {

	float x;

	float y;

};

Matrix2x2 Add(Matrix2x2 matrix1, Matrix2x2 matrix2);

Matrix2x2 Subtract(Matrix2x2 matrix1, Matrix2x2 matrix2);

Matrix2x2 Multiply(Matrix2x2 matrix1, Matrix2x2 matrix2);

Vector2 Multiply(Vector2 vector, Matrix2x2 matrix);

Matrix2x2 m1;



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

Vector2 Multiply(Vector2 vector, Matrix2x2 matrix)
{
	return Vector2();
}
