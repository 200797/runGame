#include "StartScene.h"
#include "Engine/Model.h"
#include "Engine/Image.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

StartScene::StartScene(GameObject* parent)
	: GameObject(parent, "StartScene"), hPict_(-1), pText(nullptr)
{
}

void StartScene::Initialize()
{
	hPict_ = Image::Load("kari.png");
	assert(hPict_ >= 0);

	pText = new Text;
	pText->Initialize();
}

void StartScene::Update()
{
	if (Input::IsMouseButtonDown(0) || Input::IsMouseButtonDown(1) || Input::IsMouseButtonDown(2))
	{
		SceneManager* pSceneManager = (SceneManager*)FindObject("SceneManager");
		pSceneManager->ChangeScene(SCENE_ID_PLAY);
	}
}

void StartScene::Draw()
{
	Image::SetTransform(hPict_, transform_);
	Image::Draw(hPict_);

	pText->Draw(30, 30, "Please click the mouse");
}

void StartScene::Release()
{
}
