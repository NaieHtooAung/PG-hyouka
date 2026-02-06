#include "Enemy.h"
#include "bullet.h"
#include "Player.h" 
#include <Novice.h>
#include<math.h>
void Enemy::Move() {
    if (!isAlive_) return; // 死んでたら動かさない（必要なら外してOK）

    if (!isDrop_)
    {
        pos_.x += speed_;

        // 画面端で反射（半径ぶん考慮）
        if (pos_.x > 1280.0f - radius_) {
            pos_.x = 1280.0f - radius_;
            speed_ *= -1.0f;
        }
        if (pos_.x < radius_) {
            pos_.x = radius_;
            speed_ *= -1.0f;
        }
    }
   
}

void Enemy::Respawn(const char* keys, Player& player) {
    if (keys[DIK_R]) {
        pos_ = spawnPos_;
        enemyHealth_ = 300;         // or store maxHP_ and restore it
        isAlive_ = true;
        isDrop_ = false;
        dropCD_ = 360;
        dropHitCD_ = 0;
        willDropIn_ = 20;
        recentPos_ = pos_.y;
        isHit_ = false;

        // (optional) reset player properly
        player.playerHealth_ = 100;
        player.isAlive_ = true;
    }
}

Enemy::Enemy()
{
}

void Enemy::setPosition(Vector2 pos, float radius, float speed, int enemyHealth)
{
    pos_ = pos;
    spawnPos_ = pos;
    radius_ = radius;
    speed_ = speed;
    dropCD_ = 360;
    enemyHealth_ = enemyHealth;
    isDrop_ = false;
    isAlive_ = true;
    isHit_ = false;
}
void Enemy::Update(const char* keys, Bullet& bullet, Player& player) {
    Respawn(keys, player);

    if (!isAlive_) return;

    if (dropHitCD_ > 0) dropHitCD_--;

    // ✅ reset hit flag each frame
    bool hitThisFrame = false;

    // ---------- move / drop timer ----------
    if (!isDrop_) {
        Move();

        if (dropCD_ > 0) dropCD_--;

        if (dropCD_ <= 0) {
            recentPos_ = pos_.y;
            willDropIn_ = 20;
            isDrop_ = true;
        }
    }

    //Novice::ScreenPrintf(0, 20, "willdropin: %d", willDropIn_);
    //Novice::ScreenPrintf(0, 40, "recentPos: %f", recentPos_);
    //Novice::ScreenPrintf(0, 60, "enemyPosY: %f", pos_.y);

    // ---------- drop movement ----------
    if (isDrop_) {
        float fall = (speed_ < 0 ? -speed_ : speed_);
        if (fall < 1.0f) fall = 1.0f;

        if (willDropIn_ > 0) {
            willDropIn_--;
        }
        else if (willDropIn_ == 0) {
            pos_.y += fall;

            if (pos_.y > 720.0f + radius_) {
                pos_.y = -60.0f;
                willDropIn_ = -1;
            }
        }
        else {
            pos_.y += fall;

            if (pos_.y >= recentPos_) {
                pos_.y = recentPos_;
                isDrop_ = false;
                dropCD_ = 360;
                willDropIn_ = 20;
            }
        }
    }

    // ---------- enemy shoot ----------
    if (bullet.CD_ > 0) bullet.CD_--;

    if (bullet.CD_ <= 0) {
        bullet.CD_ = 30;
        for (int i = 0; i < Bullet::kMaxCount; i++) {
            if (!bullet.isActive_[i]) {
                bullet.isActive_[i] = true;
                bullet.pos_[i] = pos_;
                break;
            }
        }
    }

    // ✅ bullet collision: do NOT set player.isHit_ inside the loop
    for (int i = 0; i < Bullet::kMaxCount; i++) {
        if (!bullet.isActive_[i]) continue;
        if (!player.isAlive_) break;

        float dx = player.pos_.x - bullet.pos_[i].x;
        float dy = player.pos_.y - bullet.pos_[i].y;
        float d2 = dx * dx + dy * dy;
        float r = bullet.radius_ + player.radius_;

        if (d2 < r * r) {
            hitThisFrame = true;
            bullet.isActive_[i] = false;
            player.playerHealth_ -= 10;
            break;
        }
    }

    // ---------- drop collision ----------
    if (isDrop_ && player.isAlive_) {
        float dx = player.pos_.x - pos_.x;
        float dy = player.pos_.y - pos_.y;
        float d2 = dx * dx + dy * dy;
        float r = radius_ + player.radius_;

        if (d2 < r * r) {
            hitThisFrame = true;

            if (dropHitCD_ == 0) {
                player.playerHealth_ -= 20;
                dropHitCD_ = 60;
            }
        }
    }

    // ✅ set hit color flag ONCE here (bullet OR drop)
    player.isHit_ = hitThisFrame;

    if (player.playerHealth_ <= 0) {
        player.playerHealth_ = 0;
        player.isAlive_ = false;
    }
}

void Enemy::Draw() const {
   /* Novice::ScreenPrintf(0, 0, "dropCD: %d", dropCD_);
    Novice::ScreenPrintf(100, 0, "health: %d", enemyHealth_);*/
    if (!isAlive_) return;
    Novice::DrawBox(
		20, 20, enemyHealth_ * 2, 20,
        0.0f,
        BLUE,
        kFillModeSolid
	);
    Novice::DrawEllipse(
        (int)pos_.x, (int)pos_.y,
        (int)radius_, (int)radius_,
        0.0f,
        RED,
        kFillModeSolid
    );
}
