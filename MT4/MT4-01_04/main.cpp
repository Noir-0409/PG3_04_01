#include <Novice.h>
#include <corecrt_math.h>
#include <cmath>
#include <cassert>

const char kWindowTitle[] = "MT4-01_04";

struct Matrix4x4 {

	float m[4][4];

};

struct Vector3 {

	float x;
	float y;
	float z;

};

struct Quaternion {

	float x;
	float y;
	float z;
	float w;

	Quaternion operator*(const Quaternion& other) const {
		return Quaternion{
			w * other.x + x * other.w + y * other.z - z * other.y,
			w * other.y - x * other.z + y * other.w + z * other.x,
			w * other.z + x * other.y - y * other.x + z * other.w,
			w * other.w - x * other.x - y * other.y - z * other.z
		};
	}
};

float Dot(const Vector3& v1, const Vector3& v2) { return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z; }
float Length(const Vector3& v) { return std::sqrt(Dot(v, v)); }

Vector3 Cross(const Vector3& v1, const Vector3& v2) {
	return { v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x };
}

Vector3 Normalize(const Vector3& v) {
	float length = Length(v);
	assert(length != 0.0f);
	return { v.x / length, v.y / length, v.z / length };
}


//任意回転をQuaternionの生成
Quaternion makeRotateAcxisAngleQuaternion(const Vector3& axis, float angle){

	Quaternion q;
	float halfAngle = angle / 2.0f;
	float sinHalfAngle = sin(halfAngle);

	q.w = cos(halfAngle);
	q.x = axis.x * sinHalfAngle;
	q.y = axis.y * sinHalfAngle;
	q.z = axis.z * sinHalfAngle;

	return q;

}

Quaternion Conjugate(const Quaternion& q) {
	return { -q.x, -q.y, -q.z, q.w };
}

//クォータニオンでベクトルを回転させる関数
Vector3 RotateVector(const Vector3& vector, const Quaternion& quaternion) {
	
	Quaternion vectorQuat = { vector.x, vector.y, vector.z, 0.0f };

	Quaternion qv = quaternion * vectorQuat * Conjugate(quaternion);

	return { qv.x, qv.y, qv.z };
}


//Quaternionから回転行列を求める
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion){

	Matrix4x4 mat;

	mat.m[0][0] = 1 - 2 * (quaternion.y * quaternion.y + quaternion.z * quaternion.z);
	mat.m[0][1] = 2 * (quaternion.x * quaternion.y + quaternion.w * quaternion.z);
	mat.m[0][2] = 2 * (quaternion.x * quaternion.z - quaternion.w * quaternion.y);
	mat.m[0][3] = 0;

	mat.m[1][0] = 2 * (quaternion.x * quaternion.y - quaternion.w * quaternion.z);
	mat.m[1][1] = 1 - 2 * (quaternion.x * quaternion.x + quaternion.z * quaternion.z);
	mat.m[1][2] = 2 * (quaternion.y * quaternion.z + quaternion.w * quaternion.x);
	mat.m[1][3] = 0;

	mat.m[2][0] = 2 * (quaternion.x * quaternion.z + quaternion.w * quaternion.y);
	mat.m[2][1] = 2 * (quaternion.y * quaternion.z - quaternion.w * quaternion.x);
	mat.m[2][2] = 1 - 2 * (quaternion.x * quaternion.x + quaternion.y * quaternion.y);
	mat.m[2][3] = 0;

	mat.m[3][0] = 0;
	mat.m[3][1] = 0;
	mat.m[3][2] = 0;
	mat.m[3][3] = 1;

	return mat;

}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {

	Vector3 transformedVector;
	transformedVector.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] + matrix.m[3][0];
	transformedVector.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] + matrix.m[3][1];
	transformedVector.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] + matrix.m[3][2];

	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] + matrix.m[3][3];
	if (w != 0.0f) {
		transformedVector.x /= w;
		transformedVector.y /= w;
		transformedVector.z /= w;
	}

	return transformedVector;
}

static const int kColumnWidth = 60;
static const int kRowHeight = 30;

void QuaternionScreenPrintf(int x,int y,const  Quaternion& quaternion, const char* label){

	Novice::ScreenPrintf(x + 220, y, "%s", label);

	Novice::ScreenPrintf(x, y, "%0.2f", quaternion.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", quaternion.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", quaternion.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%0.2f", quaternion.w);
}

void VectorScreenPrintf(int x, int y, const Vector3& vector, const char* label) {
	Novice::ScreenPrintf(x, y, "%0.2f", vector.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%0.2f", vector.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%0.2f", vector.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}

void MatrixScreenPrintf(int x, int y, const Matrix4x4& matrix, const char* label) {

	Novice::ScreenPrintf(x, y, "%s", label);

	for (int row = 0; row < 4; ++row) {
		for (int column = 0; column < 4; ++column) {
			Novice::ScreenPrintf(x + row * kColumnWidth, y + column * kRowHeight + 20, "%6.02f", matrix.m[column][row]);
		}
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

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///

		Quaternion rotation = makeRotateAcxisAngleQuaternion(Normalize(Vector3{ 1.0f,0.4f,-0.2f }), 0.45f);
		Vector3 pointY = { 2.1f,-0.9f,1.3f };
		Matrix4x4 rotateMatrix = MakeRotateMatrix(rotation);
		Vector3 rotateByQuaternion = RotateVector(pointY, rotation);
		Vector3 rotateByMatrix = Transform(pointY, rotateMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionScreenPrintf(0, kRowHeight * 0, rotation, " : rotanion");
		MatrixScreenPrintf(0, kRowHeight * 1, rotateMatrix, "rotateMatrix");
		VectorScreenPrintf(0, kRowHeight * 6, rotateByQuaternion, " : rotateByQuaternion");
		VectorScreenPrintf(0, kRowHeight * 7, rotateByMatrix, " : rotateByMatrix");

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
