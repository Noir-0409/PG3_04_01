#include <Novice.h>
#define _USE_MATH_DEFINES
#include <Math.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	
	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	float posX = 400.0f;
	float posY = 400.0f;

	float width = 200.0f;
	float high = 100.0f;
	float theta = (1.0f / 2.0f) * float(M_PI);

	const float kLeftTopX = -width / 2.0f;
	const float kRightTopX = width / 2.0f;
	const float kLeftBotomX = -width / 2.0f;
	const float kRightBotomX = width / 2.0f;
	const float kLeftTopY = -high / 2.0f;
	const float kRightTopY = high / 2.0f;
	const float kLeftBotomY = -high / 2.0f;
	const float kRightBotomY = high / 2.0f;

	float leftTopRotatedX = 0.0f;
	float rightTopRotatedX = 0.0f;
	float leftBotomRotatedX = 0.0f;
	float rightBotomRotatedX = 0.0f;
	float leftTopRotatedY = 0.0f;
	float rightTopRotatedY = 0.0f;
	float leftBotomRotatedY = 0.0f;
	float rightBotomRotatedY = 0.0f;

	float leftTopPositionX = 0.0f;
	float rightTopPsitionX = 0.0f;
	float leftBotomPositionX = 0.0f;
	float rightBotomPositionX = 0.0f;
	float leftTopPositionY = 0.0f;
	float rightTopPositionY = 0.0f;
	float leftBotomPositionY = 0.0f;
	float rightBotomPositionY = 0.0f;


	int whiteTextureHandle = Novice::LoadTexture("white1x1.png");

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
		//

		theta = 1.0f / 8.0f * float(M_PI);

		 leftTopRotatedX = kLeftTopX * cosf(theta) - kLeftTopY * sinf(theta);
		 rightTopRotatedX = kRightTopX * cosf(theta) - kRightTopY * sinf(theta);
		 leftBotomRotatedX = kLeftBotomX * cosf(theta) - kLeftBotomY * sinf(theta);
		 rightBotomRotatedX = kRightBotomX * cosf(theta) - kRightBotomY * sinf(theta);
		 leftTopRotatedY = kLeftTopY * cosf(theta) + kLeftTopX * sinf(theta);
		 rightTopRotatedY = kRightTopY * cosf(theta) + kRightTopX * sinf(theta);
		 leftBotomRotatedY = kLeftBotomY * cosf(theta) + kLeftBotomX * sinf(theta);
		 rightBotomRotatedY = kRightBotomX * cosf(theta) + kRightBotomX * sinf(theta);

		 leftTopPositionX = leftTopRotatedX + posX;
		 rightTopPsitionX = rightTopRotatedX + posX;
		 leftBotomPositionX = leftBotomRotatedX + posX;
		 rightBotomPositionX = rightBotomRotatedX + posX;
		 leftTopPositionY = leftTopRotatedY + posY;
		 rightTopPositionY = rightTopRotatedY + posY;
		 leftBotomPositionY = leftBotomRotatedY + posY;
		 rightBotomPositionY = rightBotomRotatedY + posY;
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
	
		Novice::DrawQuad(static_cast<int>(leftTopPositionX), static_cast<int>(leftTopPositionY), static_cast<int>(rightTopPsitionX), static_cast<int>(rightTopPositionY), static_cast<int>(leftBotomPositionX), static_cast<int>(leftBotomPositionY), static_cast<int>(rightBotomPositionX), static_cast<int>(rightBotomPositionY), static_cast<int>(leftTopPositionX), static_cast<int>(leftTopPositionY), 1, 1, whiteTextureHandle, 0xFFFFFFFF);
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
