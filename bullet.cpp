#include "bullet.h"
#include <Novice.h>
#include "player.h"
Bullet::Bullet() {
    speed_ = 10.0f;
    radius_ = 10.0f;
    CD_ = 15;
    for (int i = 0; i < kMaxCount; i++) {
        pos_[i] = { -100.0f, -100.0f };
        isActive_[i] = false;
    }
}

void Bullet::Move() {
    for (int i = 0; i < kMaxCount; i++) {
        if (isActive_[i]) {
            pos_[i].y -= speed_;      // Move bullet up
            // Deactivate if offscreen
            if (pos_[i].y < 0) {
                isActive_[i] = false;
                pos_[i] = { -100.0f, -100.0f };
            }
        }
    }
}

void Bullet::Draw() const {
    for (int i = 0; i < kMaxCount; i++) {
        if (isActive_[i]) {
            Novice::DrawEllipse(
                (int)pos_[i].x,
                (int)pos_[i].y,
                (int)radius_,
                (int)radius_,
                0.0f,
                WHITE,
                kFillModeSolid
            );
        }
    }
}

void Bullet::eneMove()
{
    for (int i = 0; i < kMaxCount; i++) {
        if (isActive_[i]) {
            pos_[i].y += speed_;      // Move bullet up
            // Deactivate if offscreen
            if (pos_[i].y > 720) {
                isActive_[i] = false;
                pos_[i] = { -100.0f, -100.0f };
            }
        }
    }
}

void Bullet::eneDraw() const
{
    for (int i = 0; i < kMaxCount; i++) {
        if (isActive_[i]) {
            Novice::DrawEllipse(
                (int)pos_[i].x,
                (int)pos_[i].y,
                (int)radius_,
                (int)radius_,
                0.0f,
                RED,
                kFillModeSolid
            );
        }
    }
}
