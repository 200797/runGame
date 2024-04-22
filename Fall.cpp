#include "Fall.h"
#include "Engine/Model.h"

Fall::Fall(GameObject* parent)
	: GameObject(parent, "Fall")
{
}

Fall::Fall(GameObject* parent, int xPos)
	: GameObject(parent, "Fall"), hModel_(-1)
{
	fallSpe_ = 0.1; // ��U�K���ɓ�������
	// �����ʒu
	transform_.position_ = XMFLOAT3(xPos, 10, -3);
}

void Fall::Initialize()
{
	hModel_ = Model::Load("Wall.fbx");
	assert(hModel_ >= 0);

	BoxCollider* collision = new BoxCollider(XMFLOAT3(0, 0, 0), XMFLOAT3(1, 1, 1));
	AddCollider(collision);
}

void Fall::Update()
{
	transform_.position_.y -= fallSpe_;
	// ���炩�ɖ��Q�Ȉʒu�܂ōs������
	if (transform_.position_.y < -5)
	{
		KillMe();
	}
}

void Fall::Draw()
{
	Model::SetTransform(hModel_, transform_);
	Model::Draw(hModel_);
}

void Fall::Release()
{
}
