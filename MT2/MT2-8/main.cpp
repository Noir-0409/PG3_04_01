#include <Novice.h>
#include <assert.h>
#include <math.h>
#include <Vector2.h>
struct Matrix3x3 {
	float m[3][3];
};

struct Rect {
	Vector2 LT;
	Vector2 RB;
	Vector2 center;
};
struct Camera {
	Vector2 LT;
	Vector2 RB;
};
struct View {
	Vector2 LT;
	Vector2 size;
};

Matrix3x3 createTranslateMatrix(float x, float y) {
	Matrix3x3 translationMatrix;
	translationMatrix.m[0][0] = 1.0f;
	translationMatrix.m[0][1] = 0.0f;
	translationMatrix.m[0][2] = 0.0f;;

	translationMatrix.m[1][0] = 0.0f;
	translationMatrix.m[1][1] = 1.0f;
	translationMatrix.m[1][2] = 0.0f;

	translationMatrix.m[2][0] = x;
	translationMatrix.m[2][1] = y;
	translationMatrix.m[2][2] = 1.0f;
	return translationMatrix;
}
Matrix3x3 LocalToWorldMatrix(const Rect& rect) {
	float localCenterX = rect.center.x;
	float localCenterY = rect.center.y;

	Matrix3x3 translationMatrix = createTranslateMatrix(localCenterX, localCenterY);

	return translationMatrix;
}
Matrix3x3 InverseMatrix(Matrix3x3 matrix) {
	float det =
		matrix.m[0][0] * matrix.m[1][1] * matrix.m[2][2] + matrix.m[0][1] * matrix.m[1][2] * matrix.m[2][0] + matrix.m[0][2] * matrix.m[1][0] * matrix.m[2][1] -
		matrix.m[0][2] * matrix.m[1][1] * matrix.m[2][0] - matrix.m[0][1] * matrix.m[1][0] * matrix.m[2][2] - matrix.m[0][0] * matrix.m[1][2] * matrix.m[2][1];

	float invDet = 1.0f / det;
	Matrix3x3 result;

	result.m[0][0] = (matrix.m[1][1] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][1]) * invDet;
	result.m[0][1] = -(matrix.m[0][1] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][1]) * invDet;
	result.m[0][2] = (matrix.m[0][1] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][1]) * invDet;

	result.m[1][0] = -(matrix.m[1][0] * matrix.m[2][2] - matrix.m[1][2] * matrix.m[2][0]) * invDet;
	result.m[1][1] = (matrix.m[0][0] * matrix.m[2][2] - matrix.m[0][2] * matrix.m[2][0]) * invDet;
	result.m[1][2] = -(matrix.m[0][0] * matrix.m[1][2] - matrix.m[0][2] * matrix.m[1][0]) * invDet;

	result.m[2][0] = (matrix.m[1][0] * matrix.m[2][1] - matrix.m[1][1] * matrix.m[2][0]) * invDet;
	result.m[2][1] = -(matrix.m[0][0] * matrix.m[2][1] - matrix.m[0][1] * matrix.m[2][0]) * invDet;
	result.m[2][2] = (matrix.m[0][0] * matrix.m[1][1] - matrix.m[0][1] * matrix.m[1][0]) * invDet;

	return result;


}
Matrix3x3 MakeOrthographicatrix(float left, float top, float right, float bottom) {
	Matrix3x3 result;
	result.m[0][0] = 2.0f / (right - left);
	result.m[0][1] = 0;
	result.m[0][2] = 0;

	result.m[1][0] = 0;
	result.m[1][1] = 2.0f / (top - bottom);
	result.m[1][2] = 0;

	result.m[2][0] = (left + right) / (left - right);
	result.m[2][1] = (top + bottom) / (bottom - top);
	result.m[2][2] = 1;
	return result;
}
Matrix3x3 MakeViewportMatrix(float left, float top, float widht, float height) {
	Matrix3x3 result;
	result.m[0][0] = widht / 2;
	result.m[0][1] = 0;
	result.m[0][2] = 0;
	result.m[1][0] = 0;
	result.m[1][1] = -(height / 2);
	result.m[1][2] = 0;
	result.m[2][0] = left + (widht / 2);
	result.m[2][1] = top + (height / 2);
	result.m[2][2] = 1;
	return result;
}
Matrix3x3 Multiply(Matrix3x3 matrix1, Matrix3x3 matrix2) {
	Matrix3x3 result;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			result.m[i][j] = 0;
			for (int k = 0; k < 3; k++) {
				result.m[i][j] += matrix1.m[i][k] * matrix2.m[k][j];
			}
		}
	}
	return result;
}
Vector2 Transform(Vector2 vector, Matrix3x3 matrix) {
	Vector2 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + matrix.m[2][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + matrix.m[2][1];
	float w = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + matrix.m[2][2];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	return result;
}

const char kWindowTitle[] = "MT2-8";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	float speed = 5.0f;
	float length = 0;
	Vector2 move;
	Vector2 New;
	Rect localRect =
	{
		{ -80, 80 },
		{ 80, -80 },
		{ 0, 0 }
	};
	Camera camera =
	{
		{-640,360},{640,-360}
	};
	Matrix3x3 cameraWorldMatrix;
	cameraWorldMatrix.m[0][0] = 1.0f; cameraWorldMatrix.m[0][1] = 0.0f; cameraWorldMatrix.m[0][2] = 0.0f;
	cameraWorldMatrix.m[1][0] = 0.0f; cameraWorldMatrix.m[1][1] = 1.0f; cameraWorldMatrix.m[1][2] = 0.0f;
	cameraWorldMatrix.m[2][0] = 200.0f; cameraWorldMatrix.m[2][1] = 200.0f; cameraWorldMatrix.m[2][2] = 1.0f;

	View view = {
		{0,0},{1280,720}
	};

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

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
		move.x = 0;
		move.y = 0;
		if (keys[DIK_W]) {
			move.y = speed;

		}
		if (keys[DIK_S]) {
			move.y = speed * (-1);

		}
		if (keys[DIK_A]) {
			move.x = speed * (-1);

		}

		if (keys[DIK_D]) {
			move.x = speed;

		}
		length = sqrtf(move.x * move.x + move.y * move.y);
		New.x = move.x;
		New.y = move.y;
		if (length != 0.0f) {
			New.x = move.x / length;
			New.y = move.y / length;

		}
		localRect.center.x += New.x * speed;
		localRect.center.y += New.y * speed;

		Matrix3x3 worldMatrix = LocalToWorldMatrix(localRect);
		Matrix3x3 viewMatrix = InverseMatrix(cameraWorldMatrix);
		Matrix3x3 orthoMatrix = MakeOrthographicatrix(camera.LT.x, camera.LT.y, camera.RB.x, camera.RB.y);
		Matrix3x3 viewportMatrix = MakeViewportMatrix(view.LT.x, view.LT.y, view.size.x, view.size.y);
		Matrix3x3 wvpVpMatrix = Multiply(worldMatrix, viewMatrix);

		wvpVpMatrix = Multiply(wvpVpMatrix, orthoMatrix);
		wvpVpMatrix = Multiply(wvpVpMatrix, viewportMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Vector2 screenLeftTop = Transform(localRect.LT, wvpVpMatrix);
		Novice::DrawBox(int(screenLeftTop.x), int(screenLeftTop.y), int(localRect.RB.x), int(localRect.RB.y), 0.0f, WHITE, kFillModeSolid);

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
