#include "ResultScene.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Engine/Input.h"

ResultScene::ResultScene(GameObject* parent)
{
}

ResultScene::ResultScene(GameObject* parent, int time)
	: GameObject(parent, "ResultScene"), hPict_(-1), pText(nullptr)
{
	time_ = time;
	//CoinCnt_ = CoinCnt;
}

void ResultScene::Initialize()
{
	hPict_ = Image::Load("kari.png");
	pText = new Text;
	pText->Initialize();
}

void ResultScene::Update()
{
	if (Input::IsMouseButton(0) || Input::IsMouseButton(1) || Input::IsKeyDown(DIK_SPACE))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_START);
	}
}

void ResultScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);
	// タイム
	//pText->Draw(550, 250, "Time  :      SEC");
	//pText->Draw(700, 250, time_);
	// コイン
	//pText->Draw(550, 350, "Time  :      SEC");
	//pText->Draw(700, 350, CoinCnt_);
}

void ResultScene::Release()
{
}