#include "PlayScene.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "GameTimer.h"
#include "ObstacleFactory.h"
#include <thread>
#include "ObstacleTypes.h"

GameTimer PlayScene::timer;

/*
* 4/19�A�ŏI�n�̃C���[�W�S���Ȃ�����K���ɐF�X����
* ������������͂��͂⃉���Q�[������Ȃ��̂łȂ�
*/

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), gen(std::random_device()()), pText(nullptr), lastSpawnTime(0), spawnIntervalSeconds(1)
{
	//�^�C�}�[�J�n
	timer.Start();
}

PlayScene::~PlayScene()
{
	//�^�C�}�[�I��
	timer.Stop();

	//�A�łŐi�񂶂Ⴄ���牞�}���u,�����ƃQ�[���ۂ����o����
	std::this_thread::sleep_for(std::chrono::seconds(1));

	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_RESULT, timer.GetElapsedTime());
}

void PlayScene::Initialize()
{
	//�J�����A����K���A���S�Œ肶��Ȃ�����Ȃ�N���X��
	Camera::SetPosition(XMFLOAT3(0, 6, -12));
	Camera::SetTarget(XMFLOAT3(0, 0, 4));

	Instantiate<Player>(this);

	pText = new Text;
	pText->Initialize();
}

void PlayScene::Update()
{
	// �E�B���h�E�̍X�V����~���ĂĂ����Ԑi�ނ���v���P
	// ���C�����[�v�ɐG��Ȃ��Ƃ����Ȃ��������猩�Ȃ��������Ƃɂ���

	double currentTime = timer.GetCurrentElapsedTime();
	
	// �ݒ�Ԋu�̎��Ԃ����������`�F�b�N
	if (currentTime - lastSpawnTime >= spawnIntervalSeconds)
	{
		SpawnObstacle();
		lastSpawnTime = currentTime;  //�ŏI�X�|�[�����Ԃ��X�V
	}
}

void PlayScene::Draw()
{
	// PlayScene�ɂ���܂��������̏��������Ȃ�����ǂ��ɂ�������
	pText->Draw(30, 30, "sec : ");
	pText->Draw(120, 30, timer.GetCurrentElapsedTime());
}

void PlayScene::Release()
{
}

void PlayScene::OnCollision(GameObject* pSelf)
{
	// XXXX����Փ˂����񍐖������

	if (pSelf->GetObjectName() == "Player")
	{
		KillMe();
	}
}

void PlayScene::SpawnFloor()
{
	// �����Q���Ƃقڕς��񂯂ǁA�ꉞ�ʓr��
	std::shuffle(seedTable.begin(), seedTable.end(), gen);
	for (int x = 0; x < seedTable.size(); x++)
	{
		int objectType = 0; // objectType��0�����Ȃ��
		GameObject* object = ObstacleFactory::CreateObstacle(objectType, this, seedTable[x]);
	}
}

void PlayScene::SpawnObstacle()
{
	// 3���[���̂�����2���[���ɏ�Q���o��悤�ɂ��Č����Ă��C������
	std::shuffle(seedTable.begin(), seedTable.end(), gen);
	for (int x = 0; x < seedTable.size() - 1; x++)
	{
		int objectType = RandomObjectType() + 1; // objectType��0�����Ȃ��
		GameObject* object = ObstacleFactory::CreateObstacle(objectType, this, seedTable[x]);
	}
}

int PlayScene::RandomObjectType()
{
	int typeCount = static_cast<int>(ObstacleTypes::Count);
	std::uniform_int_distribution<int> dist(1, typeCount - 1);// objectType��0�����Ȃ��0�͏o���Ȃ�
	int type = dist(gen);
	return 0;
}


