#pragma once

#include "Engine/GameObject.h"

class Normal : public GameObject
{
public:
	Normal(GameObject* parent);
	Normal(GameObject* parent, int xPos);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hModel_;
	float wScrollSpe_; //�ǂ̔����Ă��鑬��

};