#pragma once

#include <array>
#include <random>
#include "Engine/GameObject.h"
#include "Engine/Text.h"

class GameTimer;
class Player;

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
	void SpawnObstacle();
	void SpawnItem();
	int RandomObjectType(); // ���������}�V�Ȗ��O�ɂ�����

private:
	// ���ǉ���������ʓr�ł���p�̍�肻��
	std::array<int, 3> seedTable = {-1, 0, 1}; // �����œn��x���W
	std::mt19937 gen;

	double lastSpawnTime;		// 
	int spawnIntervalSeconds;	// �X�|�[���̊Ԋu
	float scrollSpe;

	Text* pText;

	static Player pChar;
};