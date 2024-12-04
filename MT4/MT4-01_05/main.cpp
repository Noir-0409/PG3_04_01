#include <Novice.h>
#include <corecrt_math.h>
#include <cmath>
#include <cassert>

const char kWindowTitle[] = "MT4-01_05";

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

	Quaternion operator-() const {
		return Quaternion{ -w, -x, -y, -z };
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
Quaternion MakeRotateAcxisAngleQuaternion(const Vector3& axis, float angle) {

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
Matrix4x4 MakeRotateMatrix(const Quaternion& quaternion) {

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

//球面線形補間
Quaternion Slerp(Quaternion& q0, Quaternion& q1, float t) {

	//q0とq1の線形補間
	float dot = q0.w * q1.w + q0.x * q1.x + q0.y * q1.y + q0.z * q1.z;

	if (dot < 0) {

		q0 = -q0;
		dot = -dot;

	}

	//なす角を求める
	float theta = std::acos(dot);

	//thetaとsinを使って補間係数scale0,scale1を求める
	float sinTheta = std::sin(theta);
	float scale0 = std::sin((1.0f - t) * theta) / sinTheta;
	float scale1 = std::sin(t * theta) / sinTheta;

	//それぞれの補間係数を利用して補間後のQuaternionを求める
	Quaternion result;
	result.w = scale0 * q0.w + scale1 * q1.w;
	result.x = scale0 * q0.x + scale1 * q1.x;
	result.y = scale0 * q0.y + scale1 * q1.y;
	result.z = scale0 * q0.z + scale1 * q1.z;

	return result;

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

void QuaternionScreenPrintf(int x, int y, const  Quaternion& quaternion, const char* label) {

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

		Quaternion rotation0 = MakeRotateAcxisAngleQuaternion({ 0.71f,0.71f,0.0f }, 0.3f);
		Quaternion rotation1 = MakeRotateAcxisAngleQuaternion({ 0.71f,0.0f,0.71f }, 3.141592f);

		Quaternion interpolate0 = Slerp(rotation0, rotation1, 0.0f);
		Quaternion interpolate1 = Slerp(rotation0, rotation1, 0.3f);
		Quaternion interpolate2 = Slerp(rotation0, rotation1, 0.5f);
		Quaternion interpolate3 = Slerp(rotation0, rotation1, 0.7f);
		Quaternion interpolate4 = Slerp(rotation0, rotation1, 1.0f);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		QuaternionScreenPrintf(0, kRowHeight * 0, interpolate0, " : interpolate0");
		QuaternionScreenPrintf(0, kRowHeight * 1, interpolate1, " : interpolate1");
		QuaternionScreenPrintf(0, kRowHeight * 2, interpolate2, " : interpolate2");
		QuaternionScreenPrintf(0, kRowHeight * 3, interpolate3, " : interpolate3");
		QuaternionScreenPrintf(0, kRowHeight * 4, interpolate4, " : interpolate4");

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
