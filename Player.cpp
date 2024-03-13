#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Engine/Image.h"
#include "Engine/SceneManager.h"
#include "Stage.h"
#include "Gauge.h"

namespace {
	const float PLAYER_MOVE_SPEED{ 5.0f / 60.0f }; //スピード
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hPlayer_(-1),speed_(PLAYER_MOVE_SPEED),pStage_(nullptr), hpCrr_(100), hpMax_(100)
{
}

void Player::Initialize()
{
	hPlayer_ = Model::Load("Player.fbx");
	assert(hPlayer_ >= 0);
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
	pStage_ = (Stage*)FindObject("Stage");

	//pText = new Text;
	//pText->Initialize();
}

void Player::Update()
{
	//enum Dir
	//{
	//	UP, DOWN, LEFT, RIGHT,NOME
	//};
	//int moveDir = Dir::NOME;
	XMVECTOR vFront = { 0,0,1,0 };
	XMVECTOR move{ 0, 0, 0, 0 };

	if (Input::IsKey(DIK_UP))
	{
		move = XMVECTOR{ 0,0,1,0 };
		//moveDir = Dir::UP;
	}
	if (Input::IsKey(DIK_LEFT))
	{
		move = XMVECTOR{ -1,0,0,0 };
		//moveDir = Dir::LEFT;
	}
	if (Input::IsKey(DIK_RIGHT))
	{
		move = XMVECTOR{ 1,0,0,0 };
		//moveDir = Dir::RIGHT;
	}
	if (Input::IsKey(DIK_DOWN))
	{
		move = XMVECTOR{ 0,0,-1,0 };
		//moveDir = Dir::DOWN;
	}

	XMVECTOR pos = XMLoadFloat3(&(transform_.position_));
	XMVECTOR posTmp = XMVectorZero(); //ゼロベクトルで初期化
	posTmp = pos + speed_ * move;

	//Debug::Log("(X, Z)=");
	//Debug::Log(XMVectorGetX(pos));
	//Debug::Log(",");
	//Debug::Log(XMVectorGetZ(pos),true);
	int tx, ty;
	tx = (int)(XMVectorGetX(posTmp) + 1.0f);
	ty = pStage_->GetStageWidth() - (int)(XMVectorGetZ(posTmp) + 1.0f);
	if (!(pStage_->IsWall(tx, ty)))
	{
		pos = posTmp;
	}
	else {
		hpCrr_ = hpCrr_ - 2;
		if (hpCrr_ < 0)
			hpCrr_ = 0;
		if (hpCrr_ == 0)
		{
			SceneManager* pSM = (SceneManager*)FindObject("SceneManager");
			pSM->ChangeScene(SCENE_ID_GAMEOVER);
		}

	}

	//Debug::Log("(!X, !Z)=");
	//Debug::Log(tx);
	//Debug::Log(",");
	//Debug::Log(ty, true);

	if (!XMVector3Equal(move, XMVectorZero()))
	{
		XMStoreFloat3(&(transform_.position_), pos);
		//XMMATRIX rot = XMMatrixRotationY(-XM_PIDIV2);
		//XMVECTOR modifiedVec = XMPlaneTransform(move, rot);
		//Debug::Log(XMVectorGetX(modifiedVec));
		//Debug::Log(",");
		//Debug::Log(XMVectorGetZ(modifiedVec), true);

		//XMVECTOR vdot = XMVector3Dot(vFront, move);
		//assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) <= 1);

		float angle = atan2(XMVectorGetX(move), XMVectorGetZ(move));

		Debug::Log("=>");
		Debug::Log(XMConvertToDegrees(-angle), true);

		//float angle = acos(XMVectorGetX(vdot));

		//XMVECTOR vCross = XMVector3Cross(vFront, move);
		//if (XMVectorGetY(vCross) < 0)
		//{
		//	angle *= -1;
		//}

		transform_.rotate_.y = XMConvertToDegrees(angle);
	}
	Gauge* pGauge = (Gauge*)FindObject("Gauge");
	pGauge->SetGaugeVal(hpCrr_, hpMax_);
}

void Player::Draw()
{
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}

void Player::Release()
{
}
