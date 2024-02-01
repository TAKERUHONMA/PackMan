#include "Player.h"
#include "Engine/Model.h"
#include "Engine/Input.h"
#include "Engine/Debug.h"
#include "Stage.h"

namespace {
	const float PLAYER_MOVE_SPEED{ 1.0f }; //スピード
}

Player::Player(GameObject* parent)
	:GameObject(parent, "Player"),hPlayer_(-1),speed_(PLAYER_MOVE_SPEED)
{
}

void Player::Initialize()
{
	hPlayer_ = Model::Load("Player.fbx");
	assert(hPlayer_ >= 0);
	transform_.position_.x = 0.5;
	transform_.position_.z = 1.5;
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
	pos = pos + speed_ * move;

	Debug::Log("(X, Y)=");
	Debug::Log(XMVectorGetX(pos));
	Debug::Log(",");
	Debug::Log(XMVectorGetX(pos),true);

	if (!XMVector3Equal(move, XMVectorZero()))
	{
		XMStoreFloat3(&(transform_.position_), pos);

		XMVECTOR vdot = XMVector3Dot(vFront, move);
		assert(XMVectorGetX(vdot) <= 1 && XMVectorGetX(vdot) <= 1);

		float angle = acos(XMVectorGetX(vdot));

		XMVECTOR vCross = XMVector3Cross(vFront, move);
		if (XMVectorGetY(vCross) < 0)
		{
			angle *= -1;
		}
		transform_.rotate_.y = XMConvertToDegrees(angle);
	}
}

void Player::Draw()
{
	Model::SetTransform(hPlayer_, transform_);
	Model::Draw(hPlayer_);
}

void Player::Release()
{
}
