#include <Novice.h>
#include<Vector2.h>
#include<math.h>
#include<assert.h>

const char kWindowTitle[] = "MT2-13";

struct Matrix3x3 {
	float m[3][3];
};

struct Camera {
	Vector2 leftTop;
	Vector2 rightBottom;
};

struct View {
	Vector2 leftTop;
	Vector2 scale;
};

Matrix3x3 MakeOrthographicMatrix(float left, float top, float right, float bottom) {
	return {
		2.0f / (right - left),
		0.0f,
		0.0f,
		0.0f,
		2.0f / (top - bottom),
		0.0f,
		(left + right) / (left - right),
		(top + bottom) / (bottom - top),
		1
	};
}

Matrix3x3 MakeViewportMatrix(float left, float top, float width, float height) {
	return {
		width / 2.0f,
		0.0f,
		0.0f,
		0.0f,
		-(height / 2.0f),
		0.0f,
		left + (width / 2.0f),
		top + (height / 2.0f),
		1
	};
}

Matrix3x3 Inverse(Matrix3x3 m2) {
	float det = (m2.m[0][0] * m2.m[1][1] * m2.m[2][2] + m2.m[0][1] * m2.m[1][2] * m2.m[2][0] + m2.m[0][2] * m2.m[1][0] * m2.m[2][1] - m2.m[0][2] * m2.m[1][1] * m2.m[2][0] - m2.m[0][1] * m2.m[1][0] * m2.m[2][2] - m2.m[0][0] * m2.m[1][2] * m2.m[2][1]);
	return {
		(m2.m[1][1] * m2.m[2][2] - m2.m[1][2] * m2.m[2][1]) / det,
		(m2.m[0][2] * m2.m[2][1] - m2.m[0][1] * m2.m[2][2]) / det,
		(m2.m[0][1] * m2.m[1][2] - m2.m[0][2] * m2.m[1][1]) / det,
		(m2.m[1][2] * m2.m[2][0] - m2.m[1][0] * m2.m[2][2]) / det,
		(m2.m[0][0] * m2.m[2][2] - m2.m[0][2] * m2.m[2][0]) / det,
		(m2.m[0][2] * m2.m[1][0] - m2.m[0][0] * m2.m[1][2]) / det,
		(m2.m[1][0] * m2.m[2][1] - m2.m[1][1] * m2.m[2][0]) / det,
		(m2.m[0][1] * m2.m[2][0] - m2.m[0][0] * m2.m[2][1]) / det,
		(m2.m[0][0] * m2.m[1][1] - m2.m[0][1] * m2.m[1][0]) / det,
	};
}

Matrix3x3 Multiply(Matrix3x3 a, Matrix3x3 b) {
	return {
		a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0],
		a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1],
		a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2],
		a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0],
		a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1],
		a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2],
		a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0],
		a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1],
		a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2],
	};
}

Matrix3x3 MakeTranslateMatrix(Vector2 translate) {
	return { 1,0,0,0,1,0,translate.x,translate.y,1 };
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



// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 480, 960);

	Camera camera{
	camera.leftTop = {0,960},
	camera.rightBottom = {480,0}
	};

	View view{
	view.leftTop = {0,0},
	view.scale = {480,960}
	};

	Matrix3x3 cameraWorldMatrix;
	cameraWorldMatrix.m[0][0] = 1.0f;
	cameraWorldMatrix.m[0][1] = 0.0f;
	cameraWorldMatrix.m[0][2] = 0.0f;
	cameraWorldMatrix.m[1][0] = 0.0f;
	cameraWorldMatrix.m[1][1] = 1.0f;
	cameraWorldMatrix.m[1][2] = 0.0f;
	cameraWorldMatrix.m[2][0] = 160.0f;
	cameraWorldMatrix.m[2][1] = 960.0f;
	cameraWorldMatrix.m[2][2] = 1.0f;

	Vector2 CenterLocal = { 160,960 };

	struct ball {
		Vector2 pos;
		int radius;
		Vector2 vel;
		Vector2 acc;
		float mass;
	};
	ball a;
	ball b;
	a.pos = { 160,960 };
	a.radius = 10;
	a.vel = { 0,0 };
	a.acc = { 0,0 };
	a.mass = -9.8f;
	b.pos = { 320,960 };
	b.radius = 10;
	b.vel = { 0,0 };
	b.acc = { 0,-9.8f };
	b.mass = 1;
	float k = 0.6f;
	Vector2 airResistance = { 0 };
	Vector2 airResistnceAcceleration = { 0 };
	bool start = false;
	Vector2 screenpos = { 160,0 };
	Vector2 screenposb = { 320,0 };

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
		if (keys[DIK_SPACE])
		{
			start = true;
		}
		if (start == true) {
			a.acc.y = -9.8f - a.vel.y * k;
			a.vel.y += a.acc.y / 60;
			a.pos.y += a.vel.y / 60;



			b.vel.y += b.acc.y / 60;
			b.pos.y += b.vel.y / 60;


			Matrix3x3 worldMatrix = MakeTranslateMatrix(a.pos);
			Matrix3x3 viewMatrix = Inverse(cameraWorldMatrix);
			Matrix3x3 orthoMatrix = MakeOrthographicMatrix(camera.leftTop.x, camera.leftTop.y, camera.rightBottom.x, camera.rightBottom.y);
			Matrix3x3 viewportMatrix = MakeViewportMatrix(view.leftTop.x, view.leftTop.y, view.scale.x, view.scale.y);

			Matrix3x3 wvpVpMatrix = Multiply(worldMatrix, viewMatrix);
			wvpVpMatrix = Multiply(wvpVpMatrix, orthoMatrix);
			wvpVpMatrix = Multiply(wvpVpMatrix, viewportMatrix);

			screenpos = Transform(a.pos, wvpVpMatrix);


			Matrix3x3 worldMatrixb = MakeTranslateMatrix(b.pos);
			Matrix3x3 viewMatrixb = Inverse(cameraWorldMatrix);
			Matrix3x3 orthoMatrixb = MakeOrthographicMatrix(camera.leftTop.x, camera.leftTop.y, camera.rightBottom.x, camera.rightBottom.y);
			Matrix3x3 viewportMatrixb = MakeViewportMatrix(view.leftTop.x, view.leftTop.y, view.scale.x, view.scale.y);

			Matrix3x3 wvpVpMatrixb = Multiply(worldMatrixb, viewMatrixb);
			wvpVpMatrixb = Multiply(wvpVpMatrixb, orthoMatrixb);
			wvpVpMatrixb = Multiply(wvpVpMatrixb, viewportMatrixb);

			screenposb = Transform(b.pos, wvpVpMatrix);
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		Novice::DrawEllipse((int)screenpos.x, (int)screenpos.y, a.radius, a.radius, 0, WHITE, kFillModeSolid);
		Novice::DrawEllipse((int)screenposb.x, (int)screenposb.y, b.radius, b.radius, 0, WHITE, kFillModeSolid);
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
