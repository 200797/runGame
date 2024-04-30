#include "PlayScene.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "GameTimer.h"
#include "ObstacleFactory.h"
#include "ItemFactory.h"
#include <thread>
#include "ObstacleTypes.h"

GameTimer PlayScene::timer;
Player PlayScene::pChar;

/*
* 4/19�A�ŏI�n�̃C���[�W�S���Ȃ�����K���ɐF�X����
* ������������͂��͂⃉���Q�[������Ȃ��̂łȂ�
* �A�C�e���֌W�̃N���X���͓K���ɂ���̂Ō�Œ�����
* ����Ă���I�u�W�F�N�g�S�ʂɂقڋ��ʂ̏��������邩��Ȃ񂩂��Ă܂Ƃ߂�
*/

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), pText(nullptr), gen(std::random_device()())
{
	lastSpawnTime = 0;
	spawnIntervalSeconds = 1;
	scrollSpe = 0.1f;

	//�^�C�}�[�J�n
	timer.Start();
}

PlayScene::~PlayScene()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_RESULT, timer.GetElapsedTime());
}

void PlayScene::Initialize()
{

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
		SpawnItem();
		lastSpawnTime = currentTime;  //�ŏI�X�|�[�����Ԃ��X�V
	}
}

void PlayScene::Draw()
{
	// PlayScene�ɂ���܂��������̏��������Ȃ�����ǂ��ɂ�������
	pText->Draw(30, 30, "sec : ");
	pText->Draw(120, 30, timer.GetCurrentElapsedTime());

	pText->Draw(30, 80, "feed: ");
	pText->Draw(120, 80, pChar.GetFeedEatCnt());

	pText->Draw(30, 130, "eat : ");
	pText->Draw(120, 130, pChar.GetGhostEatCnt());


}

void PlayScene::Release()
{
}

void PlayScene::OnCollision(GameObject* pSelf)
{
	// XXXX����Փ˂����񍐖������

	if (pSelf->GetObjectName() == "Player")
	{
		//�^�C�}�[�I��
		timer.Stop();

		//�A�łŐi�񂶂Ⴄ���牞�}���u,�����ƃQ�[���ۂ����o����
		std::this_thread::sleep_for(std::chrono::seconds(1));

		KillMe();
	}
}

void PlayScene::SpawnObstacle()
{
	// 3���[���̂�����2���[���ɏ�Q���o��悤�ɂ��Č����Ă��C������
	std::shuffle(seedTable.begin(), seedTable.end(), gen);
	for (int x = 0; x < seedTable.size() - 1; x++)
	{
		int objectType = RandomObjectType();
		GameObject* object = ObstacleFactory::CreateObstacle(objectType, this, seedTable[x], scrollSpe);
	}
}

void PlayScene::SpawnItem()
{
	// ��U�͕ǂ��o�Ȃ������ꏊ�ɏo������
	// �W�����v����Ă邵�A1�������W�ɂ��o��悤�ɂ��Ă���������
	int objectType = RandomObjectType();
	GameObject* object = ItemFactory::CreateItem(objectType, this, seedTable.back(), scrollSpe);
}

int PlayScene::RandomObjectType()
{
	int typeCount = static_cast<int>(ObstacleTypes::Count);
	std::uniform_int_distribution<int> dist(0, typeCount - 1);
	int type = dist(gen);
	return type;
}


