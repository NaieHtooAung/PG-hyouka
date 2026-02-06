#pragma once
#include "Vector.h"
#include "bullet.h"
#include "Player.h"
class Player;
class Enemy {
public:
    Enemy();

    void setPosition(Vector2 pos, float radius, float speed, int enemyHealth);
    void Update(const char* keys , Bullet& bullet, Player& player); // Move + respawn
    void Draw() const;
    Vector2 GetPos() const { return pos_; }
    float   GetRadius() const { return radius_; }
	int  GetHealth() const { return enemyHealth_; }
	bool GetisHit() const { return isHit_; }
    bool    IsAlive() const { return isAlive_; }

    void SetHit(bool hit) { isHit_ = hit; }

    void TakeDamage(int dmg) {
        enemyHealth_ -= dmg;
        if (enemyHealth_ <= 0) {
            enemyHealth_ = 0;
            isAlive_ = false;
        }
    }
private:
    void Move();
    void Respawn(const char* keys, Player& player);

private:
    Vector2 pos_;
    Vector2 spawnPos_;   // リスポーン用の初期位置
    float radius_;
    float speed_;
    int dropCD_;
    int dropHitCD_ = 0;   // cooldown frames for drop collision damage
    int enemyHealth_;
    float recentPos_ = pos_.y;
    int willDropIn_ = 20;;
    bool isAlive_;
    bool isHit_;
    bool isDrop_;
};
