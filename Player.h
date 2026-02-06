#pragma once
#include "Vector.h"
#include"bullet.h"
#include "Enemy.h"

class Enemy;

class Player
{
public:
	Player();
	void Update(const char* keys, Bullet& bullet, Enemy& enemy);
	void Draw();
	void setPosition(Vector2 position, float radius, float speed, int playerHealth);
	Vector2 pos_;
	float radius_;
	float speed_;
	int playerHealth_;
	bool isAlive_;
	bool isHit_;

private:

};