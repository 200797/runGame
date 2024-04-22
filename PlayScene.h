#pragma once

#include <array>
#include <random>
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class GameTimer;

class PlayScene : public GameObject, public GameObjectObserver
{
public:
	PlayScene(GameObject* parent);
	~PlayScene();
	void Initialize() override;
	void Update() override;
	void Draw() override;
	void Release() override;

	void OnCollision(GameObject* pSelf) override;

private:
	void SpawnFloor();
	void SpawnObstacle();
	int RandomObjectType(); // もう少しマシな名前にしたい

private:
	// 床追加したから別途でそれ用の作りそう
	std::array<int, 3> seedTable = {-1, 0, 1}; // 3レーンらしいからとりあえず
	std::mt19937 gen;

	double lastSpawnTime;		// 
	int spawnIntervalSeconds;	// スポーンの間隔

	Text* pText;

	static GameTimer timer;
};