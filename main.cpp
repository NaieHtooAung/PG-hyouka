#include <Novice.h>
#include <cstring>
#include "Enemy.h"
#include "Player.h"
#include "bullet.h"
#include"scene.h"

const char kWindowTitle[] = "GC1C_08_ネイ_トウーアウン";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int) {

    // ライブラリの初期化
    Novice::Initialize(kWindowTitle, 1280, 720);

    // キー入力結果を受け取る箱
    char keys[256] = { 0 };
    char preKeys[256] = { 0 };

    Enemy* enemy = new Enemy();
    enemy->setPosition({ 200.0f, 100.0f }, 50.0f, 10.0f,300);
    Player* player = new Player();
    player->setPosition({ 600.0f,650.0f }, 30.0f, 5.0f,100);
    Bullet playerBullet;
    Bullet enemyBullet;
    scene scn;
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
        
      // change scene by space (manual)
        if (scn.GetScene() != 1)
        {
            scn.sceneChange(keys, preKeys, *player, *enemy, playerBullet, enemyBullet);

        }
        

        if (scn.GetScene() == 1) // Game Scene
        {
            enemy->Update(keys, enemyBullet, *player);
            player->Update(keys, playerBullet, *enemy);

            playerBullet.Move();
            enemyBullet.eneMove();

            // ✅ auto scene change
            if (!enemy->IsAlive() || enemy->GetHealth() <= 0) {
                scn.SetScene(2); // Win Scene
            }
            if (!player->isAlive_ || player->playerHealth_ <= 0) {
                scn.SetScene(3); // Lose Scene
            }
        }


        ///
        /// ↑更新処理ここまで
        ///

        ///
        /// ↓描画処理ここから
        ///
      // draw game only in scene 1
        if (scn.GetScene() == 1) {
            enemy->Draw();
            player->Draw();
            playerBullet.Draw();
            enemyBullet.eneDraw();
        }
        scn.Draw();

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
