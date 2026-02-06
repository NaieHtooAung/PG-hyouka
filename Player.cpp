#include "Player.h"
#include"bullet.h"
#include "Novice.h"
#include<math.h>
#include"Enemy.h"
Player::Player()
{
}
void Player::Update(const char* keys, Bullet& bullet, Enemy& enemy)
{
	if (isAlive_)
	{
		if (keys[DIK_A])
		{
			pos_.x -= speed_;
		}
		if (keys[DIK_D])
		{
			pos_.x += speed_;
		}
		if (pos_.x > 1280.0f - radius_) {
			pos_.x = 1280.0f - radius_;
		}
		if (pos_.x < radius_) {
			pos_.x = radius_;
		}

		if (bullet.CD_ > 0)
		{
			bullet.CD_--;
		}
		// Shoot bullet
		if (keys[DIK_SPACE] && bullet.CD_ <= 0) {
			bullet.CD_ = 15; // Reset cooldown
			for (int i = 0; i < Bullet::kMaxCount; i++) {
				if (!bullet.isActive_[i]) {
					bullet.isActive_[i] = true;
					bullet.pos_[i] = pos_;  // assign player position
					break;
				}
			}
		}

		for (int i = 0; i < Bullet::kMaxCount; i++)
		{
			if (bullet.isActive_[i])
			{
				float dirX = enemy.GetPos().x - bullet.pos_[i].x;
				float dirY = enemy.GetPos().y - bullet.pos_[i].y;
				float distance = sqrtf(dirX * dirX + dirY * dirY);
				float combinedRadius = bullet.radius_ + enemy.GetRadius();

				if (distance < combinedRadius && enemy.IsAlive()) {
					enemy.TakeDamage(10);
					enemy.SetHit(true);
					bullet.isActive_[i] = false;

				}
				else {
					enemy.SetHit(false);
				}
			}

		}


	}
	

}

void Player::Draw()
{
	if (!isAlive_) return;

	Novice::DrawBox(
		20, 600, playerHealth_ * 2, 20,
		0.0f,
		WHITE,
		kFillModeSolid
	);
	if (isHit_)
	{
		Novice::DrawEllipse(
			(int)pos_.x, (int)pos_.y,
			(int)radius_, (int)radius_,
			0.0f,
			RED,
			kFillModeSolid
		);
	}
	else
	{
		Novice::DrawEllipse(
			(int)pos_.x, (int)pos_.y,
			(int)radius_, (int)radius_,
			0.0f,
			WHITE,
			kFillModeSolid
		);
	}
	
}
void Player::setPosition(Vector2 pos, float radius, float speed,int playerHealth)
{
	pos_ = pos;
	radius_ = radius;
	speed_ = speed;
	playerHealth_ = playerHealth;
	isAlive_ = true;
	isHit_ = false;
}
