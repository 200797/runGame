#pragma once

#include "Engine/GameObject.h"

class Wall : public GameObject
{
public:
	Wall(GameObject* parent);
	Wall(GameObject* parent, int xPos, float scrollSpe);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hModel_;
	float scrollSpe_;

};