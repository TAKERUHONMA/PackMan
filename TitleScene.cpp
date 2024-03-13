#include "TitleScene.h"
#include "Engine/Input.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"

TitleScene::TitleScene(GameObject* parent)
	:GameObject(parent,"TitleScene"),pText(nullptr),hTitle_(-1)
{
}

void TitleScene::Initialize()
{
	pText = new Text;
	pText->Initialize();
	hTitle_ = Image::Load("Title.png");
	assert(hTitle_ >= 0);
}

void TitleScene::Update()
{
	if (Input::IsMouseButtonUp(0))
	{
		SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
		pSM->ChangeScene(SCENE_ID_PLAY);
	}
	if (Input::IsMouseButtonUp(1))
	{
		exit(0);
	}
}

void TitleScene::Draw()
{
	pText->Draw(520, 550, "MOUSELEFT: START");
	pText->Draw(520, 600, "MOUSERIGHT: EXIT");
	Image::SetTransform(hTitle_, transform_);
	Image::Draw(hTitle_);
}

void TitleScene::Release()
{
}
