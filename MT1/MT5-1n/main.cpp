#include <Novice.h>
#define _USE_MATH_DEFINES
#include <math.h>

const char kWindowTitle[] = "LC1B_18_タムラアツキ_タイトル";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	float posX = 500.0f;
	float posY = 450.0f;
	float width = 200.0f;
	float height = 100.0f;

	float  leftTopX = posX - width / 2.0f;
	float  rightTopX = posX + width / 2.0f;
	float  leftBottomX = posX - width / 2.0f;
	float  rightBottomX = posX + width / 2.0f;

	float  leftTopY = posY - height / 2.0f;
	float  rightTopY = posY - height / 2.0f;
	float  leftBottomY = posY + height / 2.0f;
	float  rightBottomY = posY + height / 2.0f;

	float leftTopRotatedX= leftTopX;
	float rightTopRotatedX= rightTopX;
	float leftBottomRotatedX = leftBottomX;
	float rightBottomRotatedX = rightBottomX;

	float leftTopRotatedY = leftTopY;
	float rightTopRotatedY = rightTopY;
	float leftBottomRotatedY= leftBottomY;
	float rightBottomRotatedY= rightBottomY;

	float theta = 1.0f / 8.0f * (float)M_PI;

	int isPressSpace = false;

	int whiteTextureHandle = Novice::LoadTexture("white1x1.png");

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

		if (keys[DIK_SPACE]) {

			isPressSpace = true;

		}

		if (isPressSpace) {

			float localX = leftTopX - posX;
			float localY = leftTopY - posY;

			leftTopRotatedX = localX * cosf(theta) - localY * sinf(theta);
			leftTopRotatedY = localX * sinf(theta) + localY * cosf(theta);

			leftTopRotatedX += posX;
			leftTopRotatedY += posY;

			 
			localX = rightTopX - posX;
			 localY = rightTopY - posY;

			rightTopRotatedX = localX * cosf(theta) - localY * sinf(theta);
			rightTopRotatedY = localX * sinf(theta) + localY * cosf(theta);

			rightTopRotatedX += posX;
			rightTopRotatedY += posY;

			
			localX = leftBottomX - posX;
			 localY = leftBottomY - posY;

			leftBottomRotatedX = localX * cosf(theta) - localY * sinf(theta);
			leftBottomRotatedY = localX * sinf(theta) + localY * cosf(theta);

			leftBottomRotatedX += posX;
			leftBottomRotatedY += posY;


			localX = rightBottomX - posX;
			localY = rightBottomY - posY;

			rightBottomRotatedX = localX * cosf(theta) - localY * sinf(theta);
			rightBottomRotatedY = localX * sinf(theta) + localY * cosf(theta);

			rightBottomRotatedX += posX;
			rightBottomRotatedY += posY;

			theta+= 1.0f / 128.0f * (float)M_PI;
			


		}

		
		


		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Novice::DrawQuad((int)leftTopRotatedX, (int)leftTopRotatedY,
			(int)rightTopRotatedX, (int)rightTopRotatedY,
			(int)leftBottomRotatedX, (int)leftBottomRotatedY,
			(int)rightBottomRotatedX, (int)rightBottomRotatedY,
			0, 0, 32, 32, whiteTextureHandle, WHITE);

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
