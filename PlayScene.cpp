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
* 4/19、最終系のイメージ全くないから適当に色々増設
* もじもじくんはもはやランゲームじゃないのでなし
*/

PlayScene::PlayScene(GameObject* parent)
	: GameObject(parent, "PlayScene"), gen(std::random_device()()), pText(nullptr), lastSpawnTime(0), spawnIntervalSeconds(1)
{
	//タイマー開始
	timer.Start();
}

PlayScene::~PlayScene()
{
	//タイマー終了
	timer.Stop();

	//連打で進んじゃうから応急処置,ちゃんとゲームぽく演出入れ
	std::this_thread::sleep_for(std::chrono::seconds(1));

	SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
	pSceneManager->ChangeScene(SCENE_ID_RESULT, timer.GetElapsedTime());
}

void PlayScene::Initialize()
{
	//カメラ、現状適当、完全固定じゃなくするならクラスに
	Camera::SetPosition(XMFLOAT3(0, 6, -12));
	Camera::SetTarget(XMFLOAT3(0, 0, 4));

	Instantiate<Player>(this);

	pText = new Text;
	pText->Initialize();
}

void PlayScene::Update()
{
	// ウィンドウの更新が停止してても時間進むから要改善
	// メインループに触らないといけなそうだから見なかったことにする

	double currentTime = timer.GetCurrentElapsedTime();
	
	// 設定間隔の時間がしたかをチェック
	if (currentTime - lastSpawnTime >= spawnIntervalSeconds)
	{
		SpawnObstacle();
		lastSpawnTime = currentTime;  //最終スポーン時間を更新
	}
}

void PlayScene::Draw()
{
	// PlaySceneにあんまこういうの書きたくないからどうにかしたい
	pText->Draw(30, 30, "sec : ");
	pText->Draw(120, 30, timer.GetCurrentElapsedTime());
}

void PlayScene::Release()
{
}

void PlayScene::OnCollision(GameObject* pSelf)
{
	// XXXXから衝突した報告貰ったら

	if (pSelf->GetObjectName() == "Player")
	{
		KillMe();
	}
}

void PlayScene::SpawnFloor()
{
	// 現状障害物とほぼ変わらんけど、一応別途で
	std::shuffle(seedTable.begin(), seedTable.end(), gen);
	for (int x = 0; x < seedTable.size(); x++)
	{
		int objectType = 0; // objectTypeの0が床なんで
		GameObject* object = ObstacleFactory::CreateObstacle(objectType, this, seedTable[x]);
	}
}

void PlayScene::SpawnObstacle()
{
	// 3レーンのうちの2レーンに障害物出るようにって言ってた気がする
	std::shuffle(seedTable.begin(), seedTable.end(), gen);
	for (int x = 0; x < seedTable.size() - 1; x++)
	{
		int objectType = RandomObjectType() + 1; // objectTypeの0が床なんで
		GameObject* object = ObstacleFactory::CreateObstacle(objectType, this, seedTable[x]);
	}
}

int PlayScene::RandomObjectType()
{
	int typeCount = static_cast<int>(ObstacleTypes::Count);
	std::uniform_int_distribution<int> dist(1, typeCount - 1);// objectTypeの0が床なんで0は出さない
	int type = dist(gen);
	return 0;
}


