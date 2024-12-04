#include <Novice.h>
#include <cassert>
#include <cmath>

const char kWindowTitle[] = "MT4-01_03";

struct Quaternion {

	float x;
	float y;
	float z;
	float w;

};

// Quaternionの積
Quaternion Multiply(const Quaternion& lhs, const Quaternion& rhs) {
	Quaternion result;
	result.w = lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z;
	result.x = lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y;
	result.y = lhs.w * rhs.y - lhs.x * rhs.z + lhs.y * rhs.w + lhs.z * rhs.x;
	result.z = lhs.w * rhs.z + lhs.x * rhs.y - lhs.y * rhs.x + lhs.z * rhs.w;
	return result;
}

// 単位Quaternionを返す
Quaternion IdentityQuaternion() {
	return { 0.0f, 0.0f, 0.0f, 1.0f };
}

// 共役Quaternionを返す
Quaternion Conjugate(const Quaternion& quaternion) {
	return { -quaternion.x, -quaternion.y, -quaternion.z, quaternion.w };
}

// Quaternionのnormを返す
float Norm(const Quaternion& quaternion) {
	return std::sqrt(quaternion.x * quaternion.x + quaternion.y * quaternion.y +
		quaternion.z * quaternion.z + quaternion.w * quaternion.w);
}

// 正規化されたQuaternionを返す
Quaternion Normalize(const Quaternion& quaternion) {
	float norm = Norm(quaternion);
	assert(norm != 0.0f);
	return { quaternion.x / norm, quaternion.y / norm, quaternion.z / norm, quaternion.w / norm };
}

// 逆Quaternionを返す
Quaternion Inverse(const Quaternion& quaternion) {

	Quaternion conj = Conjugate(quaternion);
	float norm = Norm(quaternion);

	assert(norm != 0.0f);
	float normSquared = norm * norm;

	return { conj.x / normSquared, conj.y / normSquared, conj.z / normSquared, conj.w / normSquared };

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

		Quaternion q1 = { 2.0f,3.0f,4.0f,1.0f };
		Quaternion q2 = { 1.0f,3.0f,5.0f,2.0f };
		Quaternion identity = IdentityQuaternion();
		Quaternion conj = Conjugate(q1);
		Quaternion inv = Inverse(q1);
		Quaternion normal = Normalize(q1);
		Quaternion mul1 = Multiply(q1, q2);
		Quaternion mul2 = Multiply(q2, q1);
		float norm = Norm(q1);

		///
		/// ↑更新処理ここまで
		///

		Novice::ScreenPrintf(10, 10, "Identity: (%f, %f, %f, %f)", identity.x, identity.y, identity.z, identity.w);
		Novice::ScreenPrintf(10, 30, "Conjugate : (%f, %f, %f, %f)", conj.x, conj.y, conj.z, conj.w);
		Novice::ScreenPrintf(10, 50, "Inverse : (%f, %f, %f, %f)", inv.x, inv.y, inv.z, inv.w);
		Novice::ScreenPrintf(10, 70, "Normalized : (%f, %f, %f, %f)", normal.x, normal.y, normal.z, normal.w);
		Novice::ScreenPrintf(10, 90, "Multiply1 : (%f, %f, %f, %f)", mul1.x, mul1.y, mul1.z, mul1.w);
		Novice::ScreenPrintf(10, 110, "Multiply2 : (%f, %f, %f, %f)", mul2.x, mul2.y, mul2.z, mul2.w);
		Novice::ScreenPrintf(10, 130, "Norm : %f", norm);
		
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
