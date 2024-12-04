#include <Novice.h>

const char kWindowTitle[] = "AL10";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//　変数宣言

	// 数字の情報
	int targetNumber=65535;
	int demoninator = 10000;
	int eachNumber[5];

	//　数字の画像
	int newEachNumber[5];

	// リソース画像
	int numberGH[10] = { Novice::LoadTexture("./Resources/Images/0.png"),
	Novice::LoadTexture("./Resources/Images/1.png"),
	Novice::LoadTexture("./Resources/Images/2.png"),
	Novice::LoadTexture("./Resources/Images/3.png"),
	Novice::LoadTexture("./Resources/Images/4.png"),
	Novice::LoadTexture("./Resources/Images/5.png"),
	Novice::LoadTexture("./Resources/Images/6.png"),
	Novice::LoadTexture("./Resources/Images/7.png"),
	Novice::LoadTexture("./Resources/Images/8.png"),
	Novice::LoadTexture("./Resources/Images/9.png")};

	//　画像の横幅
	float width = 50.0f;

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};
	int number = 10000;

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

		
		//　整数を分割する処理
		for (int i = 0; i < 5; i++) {
			//10の桁乗で割る
			eachNumber[i] = targetNumber / demoninator;
			
			//次の桁に余りを送る
			targetNumber = targetNumber % demoninator;

			//次の桁の計算用に分母の桁を下げる
			demoninator = demoninator / 10;
		}

		// 数を初期化する処理
		targetNumber = 65535;
		demoninator = 10000;

		//　1フレーム毎に初期化する処理
		number = 65535;

		for (int i=0;i<5;i++)
		{
			switch (eachNumber[i]) {
			case 0:

				newEachNumber[i] = numberGH[0];

				break;

			case 1:

				newEachNumber[i] = numberGH[1];

				break;

			case 2:
				
				newEachNumber[i] = numberGH[2];

				break;

			case 3:

				newEachNumber[i] = numberGH[3];

				break;

			case 4:

				newEachNumber[i] = numberGH[4];

				break;

			case 5:

				newEachNumber[i] = numberGH[5];

				break;

			case 6:

				newEachNumber[i] = numberGH[6];

				break;

			case 7:

				newEachNumber[i] = numberGH[7];

				break;

			case 8:

				newEachNumber[i] = numberGH[8];

				break;

			case 9:

				newEachNumber[i] = numberGH[9];

				break;
			}

			
			
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		for (int i = 0; i< 5; i++)
		{
			
			Novice::DrawSprite(10+(int)width*i, 10, newEachNumber[i], 1.0f, 1.0f, 0.0f, WHITE);

		}

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
