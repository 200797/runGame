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

    //�����ʒu
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
   // �ˊтŏ����Ă邩�牘��
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


     // ��荇�����ȑf��Y���v�f
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
    // �Q�[���I�[�o�[�n�̎�ޑ����邽�т����ɏ���������̃A�z������
    // if in if�Ȃ̌������炿����ƍl��������������������
    if (pTarget->GetObjectName() == "Wall")
    {
        // ���o�����Ȃ炱�����Ȃ�
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
