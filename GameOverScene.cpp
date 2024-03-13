#include "GameOverScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"

GameOverScene::GameOverScene(GameObject* parent)
	:GameObject(parent,"GameOver")
{
}

void GameOverScene::Initialize()
{
}

void GameOverScene::Update()
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

void GameOverScene::Draw()
{
}

void GameOverScene::Release()
{
}
