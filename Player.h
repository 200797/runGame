#pragma once

#include "Engine/GameObject.h"

class Player : public GameObject
{
public:
    Player();
    Player(GameObject* parent);
    ~Player();
    void Initialize() override;
    void Update() override;
    void Draw() override;
    void Release() override;

    void OnCollision(GameObject* pTarget);

    int GetFeedEatCnt() { return feedEatCnt; };
    int GetGhostEatCnt() { return ghostEatCnt; };

private:
    int hModel_;
    // 仕様が決まってないから、名前は現在適当
    enum class PlayerState
    {
        NEUTRAL,
        MOVING,
        JUMPING,
        FALLING
    };
    PlayerState state_;

    float targetX_; // X座用しか動かく予定内からこれで
    bool IsMoving_;
   
    int feedEatCnt;
    int ghostEatCnt;
};
