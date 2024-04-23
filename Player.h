#pragma once

#include "Engine/GameObject.h"

class Player : public GameObject
{
public:
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void OnCollision(GameObject* pTarget);

private:
    int hModel_;
    // 仕様が決まってないから、名前は現在適当
    enum class PlayerState
    {
        NEUTRAL,
        JUMPING,
        FALLING
    };
    PlayerState state_;

    XMFLOAT3 PrevPosition_;
    int feedEatCnt;
    int enemyEatCnt;
    float targetX_;
    bool moving_; // 移動中かどうかを示すフラグ
};
