#include "SplashParticle.h"
#include"Novice.h"
/// コンストラクタ
SplashParticle::SplashParticle(Vector2 pos,Vector2 size)
{
	this->emitter_ = new Emitter;
	emitter_->SetPosition(pos);
	emitter_->SetSize(size);

	this->position_ = { pos };
	this->velocity_ = { 0.0f,0.0f };
	this->acceleration_ = { 0.0f,kGravity_ };
	this->size_ = { 10.0f,10.0f };
	this->isActive_ = false;
	this->mass_ = 1.0f;
	this->airResistance_ = { 0,0 };
	this->airResistanceAcceleration_ = { 0, 0 };

	this->restitution_ = 0.8f;

	this->height_ = { 0.0f,1.0f };

}

/// デストラクタ
SplashParticle::~SplashParticle()
{
	delete this->emitter_;
}

/// 初期化
void SplashParticle::Initialize()
{

}

/// 更新処理
void SplashParticle::Update()
{
	if (isActive_ == true)
	{
		position_.x = cosf(angle_.x * kDegToRad) * height_.x;
		position_.y = cosf(angle_.y * kDegToRad) * height_.y;

	}

	// 反発係数を適用して速度を反転
	velocity_.y = velocity_.y * (-restitution_);

}

/// 描画処理
void SplashParticle::Draw()
{
	if (isActive_ == true)
	{
		Novice::DrawEllipse
		(
			static_cast<int>(position_.x), static_cast<int>(position_.y),
			static_cast<int>(this->size_.x / 2), static_cast<int>(this->size_.y / 2),
			0.0f, WHITE, kFillModeSolid
		);
	}
}

