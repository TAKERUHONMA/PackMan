#include "Gauge.h"
#include "Engine/Image.h"

Gauge::Gauge(GameObject* parent)
	:GameObject(parent, "Gauge"),hGaugeBar_(-1),hGaugeFrame_(-1),gaugeMaxVal_(0),gaugeCrrVal_(0)
{
}

void Gauge::Initialize()
{
	hGaugeBar_ = Image::Load("gauge.png");
	assert(hGaugeBar_ >= 0);
	hGaugeFrame_ = Image::Load("gauge.png");
	assert(hGaugeFrame_ >= 0);

	transform_.position_.x = 0.0f;
	transform_.position_.y = 0.9f;
}

void Gauge::Update()
{
}

void Gauge::Draw()
{
	Image::SetTransform(hGaugeBar_, transform_);
	Image::Draw(hGaugeBar_);
	Image::SetTransform(hGaugeFrame_, transform_);
	Image::Draw(hGaugeFrame_);
}

void Gauge::Release()
{
}
