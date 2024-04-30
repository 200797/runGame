#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"
#include "Engine/Camera.h"


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
        if (IsMoving_)
        {
            // 目的地までの距離を計算
            float distanceToTarget = targetX_ - transform_.position_.x;

            // 移動速度を一定に
            float moveSpeed = 0.05f;

            // 目的地に近づけるようにプレイヤーを移動
            if (abs(distanceToTarget) > moveSpeed)
            {
                float direction = distanceToTarget / abs(distanceToTarget);
                transform_.position_.x += direction * moveSpeed;
            }
            else
            {
                // 到達したら位置を正確に設定し状態を変更
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
        break;

    case PlayerState::JUMPING:

        //ここでカメラを揺らしたい 
        Camera::Shake(1.0f, 0.5f, 0.1f);

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
       // KillMe();
        pTarget->KillMe();
       // NotifyCollision(this);
        return;
    }
}