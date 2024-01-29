#include "Stage.h"
#include "Engine/Model.h"
#include "Engine/Camera.h"
#include "Engine/CsvReader.h"

namespace
{
	const int STAGE_X{ 15 };
	const int STAGE_Y{ 15 };
	const int sArray[STAGE_Y][STAGE_X]{

		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,1,1,1,0,0,0,0,0,1,1,1,0,1},
		{1,0,1,0,1,0,0,0,0,0,1,0,1,0,1},
		{1,0,1,1,1,0,0,0,0,0,1,1,1,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,0,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,1,1,1,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	};
}

Stage::Stage(GameObject* parent)
	:GameObject(parent, "Stage")
{
	CsvReader csv;
	csv.Load("map.csv");
	int w = csv.GetWidth();
	int h = csv.GetHeight();


	for (int i = 0; i < STAGE_Y; i++)
	{
		vector<int> sdata(STAGE_X, 0);
		stageData_.push_back(sdata);
	}
	for (int j = 0; j < STAGE_Y; j++)
	{
		for (int i = 0; i < STAGE_X; i++)
		{
			stageData_[j][i] = csv.GetValue(i, j);
		}
	}
}

void Stage::Initialize()
{
	hFloor_ = Model::Load("Floor.fbx");
	assert(hFloor_ >= 0);
	hBlock_ = Model::Load("Wall.fbx");
	assert(hBlock_ >= 0);
	Camera::SetPosition({ 6.5,15,-3 });
	Camera::SetTarget({ 6.5, 0, 5.5 });
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
			floorTrans.position_ = { (float)x, 0 ,(float) (14 - z) };
#if 0
			if (x == 0 || z == 0 || x == 14 || z == 14)
			{
				Model::SetTransform(hBlock_, floorTrans);
				Model::Draw(hBlock_);
			}
			Model::SetTransform(hFloor_, floorTrans);
			Model::Draw(hFloor_);
#endif
			if (stageData_[z][x] == 1)
			{
				Model::SetTransform(hBlock_, floorTrans);
				Model::Draw(hBlock_);
			}
			else
			{
				Model::SetTransform(hFloor_, floorTrans);
				Model::Draw(hFloor_);
			}
		}
	}

}

void Stage::Release()
{
}
