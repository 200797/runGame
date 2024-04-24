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
    // �d�l�����܂��ĂȂ�����A���O�͌��ݓK��
    enum class PlayerState
    {
        NEUTRAL,
        MOVING,
        JUMPING,
        FALLING
    };
    PlayerState state_;

    float targetX_; // X���p�����������\������炱���
    bool IsMoving_;
   
    int feedEatCnt;
    int ghostEatCnt;
};
