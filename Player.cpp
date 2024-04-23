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

    //�����ʒu
    transform_.position_ = XMFLOAT3(0, 0, -3);

    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0.25, 0), XMFLOAT3(0.5, 0.5, 0.5));
    AddCollider(collision);
}

void Player::Update()
{
    PrevPosition_ = transform_.position_;

    // �ړ�����
    if (moving_) {
        // �ڕW���W�Ɍ������Ċ��炩�Ɉړ�����
        float direction = targetX_ - transform_.position_.x;
        if (abs(direction) > 0.01f) {
            direction /= abs(direction);
            transform_.position_.x += direction * 0.05f; // �ړ����x��K�؂Ȓl�ɒ�������K�v������܂�
        }
        else {
            transform_.position_.x = targetX_;
            moving_ = false;
        }
    }
    else {
        // �����Ɉړ�
        if (Input::IsKeyDown(DIK_S)) {
            targetX_ = 0.0f;
            moving_ = true;
        }
        // �E�ړ���X���W��+1�̈ʒu�܂ňړ��J�n
        else if (Input::IsKeyDown(DIK_D) && transform_.position_.x < 1) {
            targetX_ = 1.0f;
            moving_ = true;
        }
        // ���ړ���X���W��-1�̈ʒu�܂ňړ��J�n
        else if (Input::IsKeyDown(DIK_A) && transform_.position_.x > -1) {
            targetX_ = -1.0f;
            moving_ = true;
        }
    }

    // ��荇�����ȑf��Y���v�f
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
    // �Q�[���I�[�o�[�n�̎�ޑ����邽�т����ɏ���������̃A�z������
    if (pTarget->GetObjectName() == "Wall")
    {
        // ���o�����Ȃ炱�����Ȃ�
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
