#include "Wall.h"
#include "Engine/Model.h"

Wall::Wall(GameObject* parent)
	: GameObject(parent, "Wall")
{
}

Wall::Wall(GameObject* parent, int xPos, float scrollSpe)
	: GameObject(parent, "Wall"), hModel_(-1)
{
	transform_.position_.x = xPos;

	scrollSpe_ = scrollSpe;
}

void Wall::Initialize()
{
	hModel_ = Model::Load("Obstacle/Wall.fbx");
	assert(hModel_ >= 0);

	//�����ʒu
	transform_.position_.z = 15;

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
	AddCollider(collision);
}

void Wall::Update()
{
	transform_.position_.z -= scrollSpe_;
	if (transform_.position_.z < -5)
	{
		KillMe();
	}
}

void Wall::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Wall::Release()
{
}
