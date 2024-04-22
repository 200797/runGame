#pragma once
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class StartScene : public GameObject
{
public:
	StartScene(GameObject* parent);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hPict_;
	Text* pText;


};