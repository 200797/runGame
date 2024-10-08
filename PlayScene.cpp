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
* 4/19、最終系のイメージ全くないから適当に色々増設
* もじもじくんはもはやランゲームじゃないのでなし
* アイテム関係のクラス名は適当につけるので後で直して
* 流れてくるオブジェクト全般にほぼ共通の処理があるからなんかしてまとめろ
*/

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), pText(nullptr), gen(std::random_device()())
{
	lastSpawnTime = 0;
	spawnIntervalSeconds = 2.0;
	scrollSpe = 0.1f;

	//タイマー開始
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
	//既存のTimerが不出来だったから取り合えず無理やり、

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
	// PlaySceneにあんまこういうの書きたくないからどうにかしたい
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
	// XXXXから衝突した報告貰ったら

	if (pSelf->GetObjectName() == "Player")
	{
		//タイマー終了
		Time::End();

		//連打で進んじゃうから応急処置,ちゃんとゲームぽく演出入れ
		std::this_thread::sleep_for(std::chrono::seconds(1));

		KillMe();
	}
}

void PlayScene::SpawnObstacle()
{
	// 3レーンのうちの2レーンに障害物出るようにって言ってた気がする
	std::shuffle(seedTable.begin(), seedTable.end(), gen);
	for (int x = 0; x < seedTable.size() - 1; x++)
	{
		int objectType = RandomObjectType();
		GameObject* object = ObstacleFactory::CreateObstacle(objectType, this, seedTable[x], scrollSpe);
	}
}

void PlayScene::SpawnItem()
{
	// 一旦は壁が出なかった場所に出すだけ
	// ジャンプ入れてるし、1個高い座標にも出るようにしてもいいかも
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


