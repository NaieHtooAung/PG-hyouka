#pragma once
#include "Vector.h"

class Bullet {
public:
    static const int kMaxCount = 50;

    Bullet();
    void Move();
    void Draw() const;
    void eneMove();
    void eneDraw() const;

    Vector2 pos_[kMaxCount];
    bool isActive_[kMaxCount];
    float radius_;
    int CD_;
private:
    float speed_;
};
