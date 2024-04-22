#pragma once

#include "Engine/GameObject.h"

class Wall : public GameObject
{
public:
	Wall(GameObject* parent);
	Wall(GameObject* parent, int xPos);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hModel_;
	float wScrollSpe_; //•Ç‚Ì”—‚Á‚Ä‚­‚é‘¬‚³


};