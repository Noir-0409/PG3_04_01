#include <Novice.h>
#include "Vector2.h"

Vector2 Bezier(const Vector2& p0, const Vector2& p1, const Vector2& p2, float t) {
    return {
        (1 - t) * (1 - t) * p0.x + 2 * (1 - t) * t * p1.x + t * t * p2.x,
        (1 - t) * (1 - t) * p0.y + 2 * (1 - t) * t * p1.y + t * t * p2.y
    };
}

const char kWindowTitle[] = "MT2-10";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    Vector2 p0 = { 100,100 };
    Vector2 p1 = { 400,400 };
    Vector2 p2 = { 700,100 };
    int num = 32;

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

        for (int i = 0; i < num; i++) {
            float t0 = i / float(num);
            float t1 = (i + 1) / float(num);
            Vector2 bezier0 = Bezier(p0, p1, p2, t0);
            Vector2 bezier1 = Bezier(p0, p1, p2, t1);
            Novice::DrawLine(int(bezier0.x), int(bezier0.y) * -1 + 500, int(bezier1.x), int(bezier1.y) * -1 + 500, BLUE);
        }

        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///

        Novice::DrawEllipse(int(p0.x), int(p0.y) * -1 + 500, 10, 10, 0.0f, WHITE, kFillModeSolid);
        Novice::DrawEllipse(int(p1.x), int(p1.y) * -1 + 500, 10, 10, 0.0f, WHITE, kFillModeSolid);
        Novice::DrawEllipse(int(p2.x), int(p2.y) * -1 + 500, 10, 10, 0.0f, WHITE, kFillModeSolid);
        Novice::DrawLine(0, 550, 1280, 550, RED);
        Novice::DrawLine(180, 0, 180, 720, GREEN);

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
