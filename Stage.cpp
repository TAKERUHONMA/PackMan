#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Floor.fbx");
	assert(hFloor_ >= 0);
	hBlock_ = Model::Load("Wall.fbx");
	assert(hBlock_ >= 0);
	Camera::SetPosition({ 6.5,10,-5 });
	Camera::SetTarget({ 6.5,0,5.5 });
}

void Stage::Update()
{
}

void Stage::Draw()
{
	Transform floorTrans;
	for (int z = 0; z < 15; z++)
	{
		for (int x = 0; x < 15; x++)
		{
			floorTrans.position_ = { (float)x, 0 ,(float)z };
			if (x == 0 || z == 0 || x == 14 || z == 14)
			{
				Model::SetTransform(hBlock_, floorTrans);
				Model::Draw(hBlock_);
			}
			Model::SetTransform(hFloor_, floorTrans);
			Model::Draw(hFloor_);
		}
	}

}

void Stage::Release()
{
}
