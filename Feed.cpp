#include "Feed.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "PlayScene.h"


Feed::Feed(GameObject* parent)
{
}

Feed::Feed(GameObject* parent, int xPos, float scrollSpe)
    : GameObject(parent, "Feed"), hModel_(-1)
{
    //‰ŠúˆÊ’u
    transform_.position_ = XMFLOAT3(xPos, 0, 15);
    scrollSpe_ = scrollSpe;
}

Feed::~Feed()
{
}

void Feed::Initialize()
{
    hModel_ = Model::Load("Item/Player.fbx");
    assert(hModel_ >= 0);

    BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0.25, 0), XMFLOAT3(0.5, 0.5, 0.5));
    AddCollider(collision);
}

void Feed::Update()
{
    transform_.position_.z -=scrollSpe_;
}


void Feed::Draw()
{
    Model::SetTransform(hModel_, transform_);
    Model::Draw(hModel_);
}

void Feed::Release()
{
}