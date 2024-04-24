#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"


Player::Player()
{
}

Player::Player(GameObject* parent)
    : GameObject(parent, "Player"),
    hModel_(-1),
    state_(PlayerState::NEUTRAL),
    IsMoving_(true),
    feedEatCnt(0)
{
    PlayScene* playScene = FindObject<PlayScene>("PlayScene");
    if (playScene)
    {
        AttachObserver(playScene);
    }
}

Player::~Player()
{
}

void Player::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    //初期位置
    transform_.position_ = XMFLOAT3(0, 0, -3);

    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0.25, 0), XMFLOAT3(0.5, 0.5, 0.5));
    AddCollider(collision);
}

void Player::Update()
{
    switch (state_)
    {
    case PlayerState::NEUTRAL:
        if (Input::IsKeyDown(DIK_SPACE))
        {
            state_ = PlayerState::JUMPING;
        }
        if (Input::IsMouseButtonDown(0) || Input::IsMouseButtonDown(1))
        {
            state_ = PlayerState::MOVING;
        }
        break;
    case PlayerState::MOVING:
   // 突貫で書いてるから汚い
        if (IsMoving_)
        {
            float direction = targetX_ - transform_.position_.x;
            if (abs(direction) > 0.01f)
            {
                direction /= abs(direction);
                transform_.position_.x += direction * 0.05f;
            }
            else
            {
                transform_.position_.x = targetX_;
                IsMoving_ = false;
                state_ = PlayerState::NEUTRAL;
            }
        }
        else
        {
            if (Input::IsMouseButtonUp(1) && transform_.position_.x < 1)
            {
                targetX_ = transform_.position_.x + 1.0f;
                IsMoving_ = true;
            }
            else if (Input::IsMouseButtonUp(0) && transform_.position_.x > -1)
            {
                targetX_ = transform_.position_.x - 1.0f;
                IsMoving_ = true;
            }
        }


     // 取り合えず簡素なY軸要素
    case PlayerState::JUMPING:
        transform_.position_.y += 0.1f;
        if (transform_.position_.y >= 2.0f)
        {
            state_ = PlayerState::FALLING;
        }
        break;

    case PlayerState::FALLING:
        transform_.position_.y -= 0.1f;
        if (transform_.position_.y <= 0.0f)
        {
            transform_.position_.y = 0.0f;
            state_ = PlayerState::NEUTRAL;
        }
        break;
    }
}


void Player::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Player::Release()
{
}

void Player::OnCollision(GameObject* pTarget)
{
    // ゲームオーバー系の種類増えるたびここに条件増えるのアホくさい
    // if in ifなの嫌だからちょっと考え直した方がいいかも
    if (pTarget->GetObjectName() == "Wall")
    {
        // 演出入れるならここかなぁ
        if (feedEatCnt >= 4)
        {
            pTarget->KillMe();
            feedEatCnt -= 4;
            ghostEatCnt++;
            return;
        }
        else 
        {
            KillMe();
            pTarget->KillMe();
            NotifyCollision(this);
            return;
        }
        
    }
    if (pTarget->GetObjectName() == "Feed")
    {
        feedEatCnt++;
    }
}
