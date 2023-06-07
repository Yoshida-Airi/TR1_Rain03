#include "Emitter.h"
#include"Novice.h"

/// コンストラクタ
Emitter::Emitter()
{
	this->position_ = { 0.0f,32.0f };
	this->size_ = { 1280.0f,16.0f };
}

/// デストラクタ
Emitter::~Emitter()
{

}

//描画
void Emitter::Draw()
{
	Novice::DrawBox
	(
		static_cast<int>(this->position_.x), static_cast<int>(this->position_.y),
		static_cast<int>(this->size_.x), static_cast<int>(this->size_.y),
		0.0f, WHITE, kFillModeWireFrame
	);
}

void Emitter::SetPosition(Vector2 pos)
{
	this->position_ = pos;
}

void Emitter::SetSize(Vector2 size)
{
	this->size_ = size;
}