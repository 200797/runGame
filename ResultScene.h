#pragma once

#include "Engine/GameObject.h"
#include "Engine/Text.h"

class GameTimer;

class ResultScene : public GameObject
{
public:
	ResultScene(GameObject* parent);
	ResultScene(GameObject* parent, int time);
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

private:
	int hPict_;
	Text* pText;

	int time_;


};