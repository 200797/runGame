#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"


Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), state_(PlayerState::NEUTRAL), feedEatCnt(0), enemyEatCnt(0)
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
    PrevPosition_ = transform_.position_;

    // 移動処理
    if (moving_) {
        // 目標座標に向かって滑らかに移動する
        float direction = targetX_ - transform_.position_.x;
        if (abs(direction) > 0.01f) {
            direction /= abs(direction);
            transform_.position_.x += direction * 0.05f; // 移動速度を適切な値に調整する必要があります
        }
        else {
            transform_.position_.x = targetX_;
            moving_ = false;
        }
    }
    else {
        // 中央に移動
        if (Input::IsKeyDown(DIK_S)) {
            targetX_ = 0.0f;
            moving_ = true;
        }
        // 右移動でX座標が+1の位置まで移動開始
        else if (Input::IsKeyDown(DIK_D) && transform_.position_.x < 1) {
            targetX_ = 1.0f;
            moving_ = true;
        }
        // 左移動でX座標が-1の位置まで移動開始
        else if (Input::IsKeyDown(DIK_A) && transform_.position_.x > -1) {
            targetX_ = -1.0f;
            moving_ = true;
        }
    }

    // 取り合えず簡素なY軸要素
    switch (state_)
    {
    case PlayerState::NEUTRAL:
        if (Input::IsKeyDown(DIK_SPACE))
        {
            state_ = PlayerState::JUMPING;
        }
        break;

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
    if (pTarget->GetObjectName() == "Wall")
    {
        // 演出入れるならここかなぁ
        KillMe();
        pTarget->KillMe();
        NotifyCollision(this);
    }

    if (pTarget->GetObjectName() == "Feed")
    {
        pTarget->KillMe();
        feedEatCnt++;
    }
}
