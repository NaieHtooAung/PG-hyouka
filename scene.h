#pragma once

class Player;
class Enemy;
class Bullet;

class scene {
public:
    scene();

    void sceneChange(const char* keys, const char* preKeys,
        Player& player, Enemy& enemy, Bullet& playerBullet, Bullet& enemyBullet);

    void Draw() const;

    int GetScene() const { return sceneNum_; }
    void SetScene(int n) { sceneNum_ = n; }

private:
    int sceneNum_ = 0;
};
