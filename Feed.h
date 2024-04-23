#pragma once

#include "Engine/GameObject.h"

class Feed : public GameObject
{
public:
	Feed(GameObject* parent);
	Feed(GameObject* parent, int xPos, float scrollSpe);
	~Feed();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hModel_;
	float scrollSpe_;
};