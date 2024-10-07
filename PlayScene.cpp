#include "PlayScene.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/SceneManager.h"
#include "Player.h"
#include "Wall.h"
#include "ObstacleFactory.h"
#include "ItemFactory.h"
#include <thread>
#include "ObstacleTypes.h"
#include "Time.h"

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
	spawnIntervalSeconds = 2.0;
	scrollSpe = 0.1f;

	//�^�C�}�[�J�n
	Time::Start();
}

PlayScene::~PlayScene()
{
	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_RESULT);
}

void PlayScene::Initialize()
{

	player = Instantiate<Player>(this);

	pText = new Text;
	pText->Initialize();
}

void PlayScene::Update()
{
	//������Timer���s�o�������������荇�����������A

	static auto lastSpawnTime = std::chrono::steady_clock::now();
	auto currentTime = std::chrono::steady_clock::now();

	std::chrono::duration<float> elapsedTime = currentTime - lastSpawnTime;

	if (elapsedTime.count() >= spawnIntervalSeconds)
	{
		SpawnObstacle();
		SpawnItem();
		lastSpawnTime = currentTime;
	}
}

void PlayScene::Draw()
{
	// PlayScene�ɂ���܂��������̏��������Ȃ�����ǂ��ɂ�������
	//pText->Draw(30, 30, "sec : ");
	//pText->Draw(120, 30, Time::ElapsedTime());
	

	pText->Draw(30, 80, "feed: ");
	pText->Draw(120, 80, player->GetFeedEatCnt());

	//pText->Draw(30, 130, "eat : ");
	//pText->Draw(120, 130, pChar.GetGhostEatCnt());


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
		Time::End();

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


