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
    // �d�l�����܂��ĂȂ�����A���O�͌��ݓK��
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
    bool moving_; // �ړ������ǂ����������t���O
};
