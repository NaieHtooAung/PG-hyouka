    #include "scene.h"
    #include <Novice.h>
    #include "Player.h"
    #include "Enemy.h"
    #include "bullet.h"

    scene::scene() { sceneNum_ = 0; }
    void scene::sceneChange(const char* keys, const char* preKeys, Player& player, Enemy& enemy, Bullet& playerBullet, Bullet& enemyBullet)
    {
        if (keys[DIK_SPACE] && !preKeys[DIK_SPACE]) {
            sceneNum_++;
            if (sceneNum_ >= 1) sceneNum_ = 1;
            if (sceneNum_ > 3) sceneNum_ = 0;
        }

        if ((sceneNum_ == 2 || sceneNum_ == 3) && keys[DIK_R] && !preKeys[DIK_R]) {
            player.setPosition({ 600.0f,650.0f }, 30.0f, 5.0f, 100);
            enemy.setPosition({ 200.0f, 100.0f }, 50.0f, 10.0f, 300);

            // ✅ reset bullets correctly (the same ones used in main)
            for (int i = 0; i < Bullet::kMaxCount; i++) {
                playerBullet.isActive_[i] = false;
                enemyBullet.isActive_[i] = false;
                playerBullet.pos_[i] = { -100.0f, -100.0f };
                enemyBullet.pos_[i] = { -100.0f, -100.0f };
            }

            // also reset cooldown so no instant spawn
            playerBullet.CD_ = 15;
            enemyBullet.CD_ = 15;

            sceneNum_ = 1;
        }
    }

    void scene::Draw() const
    {
        int graphHandle1 = Novice::LoadTexture("./images/CircleGamestart.png");
        int graphHandle2 = Novice::LoadTexture("./images/CircleYouWin.png");
        int graphHandle3 = Novice::LoadTexture("./images/CircleYouLose.png");
        Novice::ScreenPrintf(0, 0, "sceneNum: %d", sceneNum_);
        if (sceneNum_ == 0) {
            Novice::DrawSprite(0, 0, graphHandle1, 1.0f, 1.0f, 0.0f, WHITE);
        }
            if (sceneNum_ == 1) Novice::ScreenPrintf(600, 360, "Game Scene");
            if (sceneNum_ == 2) {
                Novice::DrawSprite(0, 0, graphHandle2, 1.0f, 1.0f, 0.0f, WHITE);
            }
            if (sceneNum_ == 3) {
                Novice::DrawSprite(0, 0, graphHandle3, 1.0f, 1.0f, 0.0f, WHITE);
            }

            }
