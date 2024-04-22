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
	float fallSpe_; // �������Ƃ������܂����疼�O�ς��Ƃ�
};