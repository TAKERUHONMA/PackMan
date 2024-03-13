#include "GameOverScene.h"
#include "Engine/Input.h"
#include "Engine/SceneManager.h"
#include "Engine/Image.h"

GameOverScene::GameOverScene(GameObject* parent)
	:GameObject(parent,"GameOver"),hOver_(-1)
{
}

void GameOverScene::Initialize()
{
	pText = new Text;
	pText->Initialize();
	hOver_ = Image::Load("GameOver.png");
	assert(hOver_ >= 0);
}

void GameOverScene::Update()
{
	if (Input::IsMouseButtonUp(0))
	{
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_TITLE);
	}
	if (Input::IsMouseButtonUp(1))
	{
		exit(0);
	}
}

void GameOverScene::Draw()
{
	Image::SetTransform(hOver_, transform_);
	Image::Draw(hOver_);
	pText->Draw(500, 500, "MOUSELEFT: TITLE");
	pText->Draw(500, 550, "MOUSERIGHT: EXIT");
}

void GameOverScene::Release()
{
}
