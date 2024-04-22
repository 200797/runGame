#include "Normal.h"
#include "Engine/Model.h"

Normal::Normal(GameObject* parent)
	: GameObject(parent, "Normal")
{
}

Normal::Normal(GameObject* parent, int xPos)
	: GameObject(parent, "Normal"), hModel_(-1)
{
	transform_.position_.x = xPos;

	wScrollSpe_ = 0.1f;
}

void Normal::Initialize()
{
	hModel_ = Model::Load("Normal.fbx");
	assert(hModel_ >= 0);

	//èâä˙à íu
	transform_.position_.z = 15;

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
	AddCollider(collision);
}

void Normal::Update()
{
	transform_.position_.z -= wScrollSpe_;
	if (transform_.position_.z < -5)
	{
		KillMe();
	}
}

void Normal::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Normal::Release()
{
}
