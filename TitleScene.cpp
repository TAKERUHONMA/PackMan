#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene"),pText(nullptr)
{
}

void TitleScene::Initialize()
{
	pText = new Text;
	pText->Initialize();
}

void TitleScene::Update()
{
	if (Input::IsMouseButton(0))
	{
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_PLAY);
	}
	if (Input::IsMouseButton(1))
	{
		exit(0);
	}
}

void TitleScene::Draw()
{
	pText->Draw(500, 500, "MOUSELEFT: START");
	pText->Draw(500, 550, "MOUSERIGHT: EXIT");
}

void TitleScene::Release()
{
}
