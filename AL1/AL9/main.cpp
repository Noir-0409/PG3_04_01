#include <Novice.h>

const char kWindowTitle[] = "AL9";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	//　変数宣言

	// 音の情報
	int soundHandle1 = Novice::LoadAudio("./Sounds/fanfare.wav");
	int soundHandle2 = Novice::LoadAudio("./Sounds/mokugyo.wav");
	int soundHandle3 = Novice::LoadAudio("./Sounds/start.wav");

	//　再生状況を管理する変数
	int voiceHandle1 = -1;
	int voiceHandle2 = -1;
	int voiceHandle3 = -1;



	// シーン画面
	enum SCENE {
		FIRST,
		SECOND,
		THIRD
	};

	int scene = FIRST;

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

		//　シーン切り替え処理
		switch (scene) {
		case FIRST:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

				scene = SECOND;
			}
			break;

		case SECOND:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

				scene = THIRD;
			}
			break;

		case THIRD:
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == false) {

				scene = FIRST;
			}
			break;
		}

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		switch (scene) {
		case FIRST:
			Novice::StopAudio(voiceHandle3);
			if (Novice::IsPlayingAudio(voiceHandle1) == 0 || voiceHandle1 == -1) {
				voiceHandle1 = Novice::PlayAudio(soundHandle1, true, 0.5f);
			}

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, RED, kFillModeSolid);

			break;

		case SECOND:
			Novice::StopAudio(voiceHandle1);
			if (Novice::IsPlayingAudio(voiceHandle2) == 0 || voiceHandle2 == -1) {
				voiceHandle2 = Novice::PlayAudio(soundHandle2, true, 0.5f);
			}

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, BLUE, kFillModeSolid);

			break;

		case THIRD:
			Novice::StopAudio(voiceHandle2);
			if (Novice::IsPlayingAudio(voiceHandle3) == 0 || voiceHandle3 == -1) {
				voiceHandle3 = Novice::PlayAudio(soundHandle3, true, 0.5f);
			}

			Novice::DrawBox(0, 0, 1280, 720, 0.0f, GREEN, kFillModeSolid);

			break;
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
