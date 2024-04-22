#pragma once

#include "Engine/GameObject.h"

class Fall : public GameObject
{
public:
	Fall(GameObject* parent);
	Fall(GameObject* parent, int xPos);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hModel_;
	float fallSpe_; // 落っことす物決まったら名前変えとけ
};