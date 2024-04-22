#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"


Player::Player(GameObject* parent)
    : GameObject(parent, "Player"), hModel_(-1), state_(PlayerState::NEUTRAL)
{
    PlayScene* playScene = FindObject<PlayScene>("PlayScene");
    if (playScene)
    {
        AttachObserver(playScene);
    }
}

void Player::Initialize()
{
    hModel_ = Model::Load("Player.fbx");
    assert(hModel_ >= 0);

    //‰ŠúˆÊ’u
    transform_.position_ = XMFLOAT3(0, 0, -3);

    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0.25, 0), XMFLOAT3(0.5, 0.5, 0.5));
    AddCollider(collision);
}

void Player::Update()
{
    if (Input::IsMouseButtonDown(0) && transform_.position_.x > -1)
    {
        transform_.position_.x -= 1;
    }
    if (Input::IsMouseButtonDown(1) && transform_.position_.x < 1)
    {
        transform_.position_.x += 1;
    }

    // Žæ‚è‡‚¦‚¸ŠÈ‘f‚ÈYŽ²—v‘f
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
    // Ží—Þ‘‚¦‚é‚½‚Ñ‚±‚±‚ÉðŒ‘‚¦‚é‚ÌƒAƒz‚­‚³‚¢
    if (pTarget->GetObjectName() == "Wall" || pTarget->GetObjectName() == "Fall")
    {
        KillMe();
        pTarget->KillMe();
        NotifyCollision(this);
    }
}
