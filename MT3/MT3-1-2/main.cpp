#include <Novice.h>
#include <cstdint>
#define _USE_MATH_DEFINES
#include <Math.h>
#include <imgui.h>

const char kWindowTitle[] = "MT3-1-2";

struct Matrix4x4 {

	float m[4][4];

};

struct Vector3 {

	float x;
	float y;
	float z;

};

//座標変換
Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {

	// 変換後のベクトル
	Vector3 transformedVector;

	// 行列とベクトルの乗算
	transformedVector.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	transformedVector.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	transformedVector.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];

	// ベクトルの4番目の成分が1でない場合、正規化する
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
	if (w != 0.0f) {
		transformedVector.x /= w;
		transformedVector.y /= w;
		transformedVector.z /= w;
	}

	return transformedVector;

}

Vector3 SphericalToCartesian(float lat, float lon, float radius) {
	Vector3 result;
	result.x = radius * cos(lat) * cos(lon);
	result.y = radius * sin(lat);
	result.z = radius * cos(lat) * sin(lon);
	return result;
}

// ビューポート変換行列
Matrix4x4 MakeViewportMatrix(float left, float top, float width, float height, float minDepth, float maxDepth) {

	Matrix4x4 viewportMatrix;

	viewportMatrix.m[0][0] = width / 2.0f;
	viewportMatrix.m[0][1] = 0;
	viewportMatrix.m[0][2] = 0;
	viewportMatrix.m[0][3] = 0;

	viewportMatrix.m[1][0] = 0;
	viewportMatrix.m[1][1] = -height / 2.0f;
	viewportMatrix.m[1][2] = 0;
	viewportMatrix.m[1][3] = 0;

	viewportMatrix.m[2][0] = 0;
	viewportMatrix.m[2][1] = 0;
	viewportMatrix.m[2][2] = maxDepth - minDepth;
	viewportMatrix.m[2][3] = minDepth;

	viewportMatrix.m[3][0] = left + width / 2.0f;
	viewportMatrix.m[3][1] = top + height / 2.0f;
	viewportMatrix.m[3][2] = 0;
	viewportMatrix.m[3][3] = 1;

	return viewportMatrix;

}

// 行列の積
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {

	Matrix4x4 result;

	// 行列の各要素について、行列の積を計算する
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 4; ++j) {
			result.m[i][j] = 0; // 初期化しておく
			for (int k = 0; k < 4; ++k) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	// 結果の行列を返す
	return result;

}

struct Sphere{

	Vector3 center;
	float radius;

};

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectMatrix, const Matrix4x4& viewPortmatrix, uint32_t color) {

	const uint32_t kSubdivision = 12;

	const float kLonEvery = 45;
	const float kLatEvery = 45;

	const float theta = M_PI / kSubdivision;
	const float phi = 2 * M_PI / kSubdivision;

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {

		float lat = float(- M_PI) / 2.0f + kLatEvery * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {

			float lon = lonIndex * kLonEvery;

			//world座標系でのa,b,cを求める
		//	Vector3 a={cos(theta),cos(phi)}

			

			// ab,bcで線を引く
			/*Novice::DrawLine((int)a.x, (int)a.y, (int)b.x, (int)b.y, color);

			Novice::DrawLine((int)b.x, (int)b.y, (int)c.x, (int)c.y, color);*/

		}

	}

}

void DrawGrid(const Matrix4x4 viewProjectMatrix, const Matrix4x4& viewportMatrix) {

	const float kGridHalfWidth = 2.0f;

	const uint32_t kSubdivision = 10;

	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	// 奥から手前に線を引く
	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {

		float x = -kGridHalfWidth + (xIndex * kGridEvery);

		unsigned int color = 0xAAAAAAAFF;

		// ワールド座標上の始点と終点
		Vector3 start{ x,0.0f,-kGridHalfWidth };
		Vector3 end{ x,0.0f,kGridHalfWidth };

		// スクリーン座標まで変換
		Vector3 startScreen = Transform(Transform(start, viewProjectMatrix), viewportMatrix);
		Vector3 endScreen = Transform(Transform(end, viewProjectMatrix), viewportMatrix);

		// 表示
		if (x == 0.0f) {

			color = BLACK;

		}

		Novice::DrawLine((int)startScreen.x, (int)startScreen.y, (int)endScreen.x, (int)endScreen.y, color);

	}

	for (uint32_t zIndex = 0; zIndex <= kSubdivision; ++zIndex) {

		float z= -kGridHalfWidth + (zIndex * kGridEvery);

		float color = 0xAAAAAAFF;

		Vector3 start{ z,0.0f,-kGridHalfWidth };

		Vector3 end{ z,0.0f,kGridHalfWidth };

		Vector3 startScreen = Transform(Transform(start, viewProjectMatrix), viewportMatrix);

		Vector3 endScreen = Transform(Transform(end, viewProjectMatrix), viewportMatrix);

		if (z == 0.0f) {

			color = BLACK;

		}

		Novice::DrawLine((int)startScreen.x, (int)startScreen.y, (int)endScreen.x, (int)endScreen.y, (int)color);

	}

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

		Vector3 cameraTranslate{ 0.0f,1.9f,-6.49f };

		Vector3 cameraRotate{ 0.26f,0.0f,0.0f };

		Sphere sphere{

			{0,0,0},

			1.0f,

		};

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		ImGui::Begin("Window");
		ImGui::DragFloat3("CameraTranslate", &cameraTranslate.x, 0.01f);
		ImGui::DragFloat3("CameraRotate", &cameraRotate.x, 0.01f);
		ImGui::DragFloat3("SphereCenter", &sphere.center.x, 0.01f);
		ImGui::DragFloat("Sphereradius", &sphere.radius, 0.01f);
		ImGui::End();

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
