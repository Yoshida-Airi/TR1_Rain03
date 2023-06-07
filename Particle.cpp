#include "Particle.h"
#include"Novice.h"
//コンストラクタ
Particle::Particle()
{
	this->emitter_ = new Emitter;


	this->position_ = { 0.0f,0.0f };
	this->velocity_ = { 0.0f,0.0f };
	this->acceleration_ = { 0.0f,kGravity_ };
	this->size_ = { 10.0f,10.0f };
	this->isActive_ = false;
	this->mass_ = 10.0f;
	this->airResistance_ = { 0,0 };
	this->airResistanceAcceleration_ = { 0, 0 };
		

	this->restitution_ = 0.8f;
	this->ground_ = { 0,700 };

}


//デストラクタ
Particle::~Particle()
{
	delete emitter_;
	
}

//更新処理
void Particle::Update()
{
	//もし生成されていなかったら
	if (this->isActive_ == false )
	{
		//エミッターの位置からランダムに位置を決める
		Vector2 min;
		Vector2 max;

		min.x = emitter_->GetPosition().x;
		max.x = emitter_->GetSize().x;
		min.y = emitter_->GetPosition().x + emitter_->GetSize().x / 2;
		max.y = emitter_->GetPosition().y - emitter_->GetSize().y / 4;

		this->position_.x = min.x + static_cast<float>(rand()) / RAND_MAX * (max.x - min.x);
		this->position_.y = emitter_->GetPosition().y - static_cast<float>(rand()) / RAND_MAX * 1280.0f; // 100.0fはランダムな範囲の大きさを調整する値


		//生成する
		this->isActive_ = true;
		
	}

	//生成されていたら
	if (this->isActive_ == true)
	{
		//空気抵抗
		airResistance_ =
		{
			(this->k_ * -this->velocity_.x),
			(this->k_ * -this->velocity_.y)
		};

		//空気抵抗による加速度
		airResistanceAcceleration_ =
		{
			-airResistance_.x / this->mass_,
			-airResistance_.y / this->mass_
		};

		this->acceleration_.y = kGravity_ + airResistanceAcceleration_.y;

		//速度を一定時間ごとに一定距離進ませる
		this->velocity_.x += this->acceleration_.x * (1.0f / 60.0f);
		this->velocity_.y += this->acceleration_.y * (1.0f / 60.0f);

		//位置に速度を足す(進む)
		this->position_.x += this->velocity_.x * (1.0f / 60.0f);
		this->position_.y += this->velocity_.y * (1.0f / 60.0f);

		if (position_.y >= 720)
		{
			isActive_ = false;
			this->velocity_ = { 0.0f,0.0f };
		
		}
	}

	//地面に当たったときの跳ね返り
	if (this->isActive_ == true && this->position_.y >= this->ground_.y)
	{
		
		isActive_ = false;

		// 跳ね返る速度の計算
		this->velocity_.y = -this->velocity_.y * this->restitution_;

		// パーティクルを地面の少し上に移動して、はまらないようにする
		this->position_.y = this->ground_.y - this->size_.y / 2 - 1.0f;
	}

}



//描画
void Particle::Draw()
{
	Novice::DrawLine
	(
		static_cast<int>(this->ground_.x), static_cast<int>(this->ground_.y),
		static_cast<int>(this->ground_.x + 1280), static_cast<int>(this->ground_.y),
		RED
	);

	//円の描画
	if (this->isActive_ == true)	//生成されていたら描画する
	{
		Novice::DrawEllipse
		(
			static_cast<int>(position_.x), static_cast<int>(position_.y),
			static_cast<int>(this->size_.x / 2), static_cast<int>(this->size_.y / 2),
			0.0f, WHITE, kFillModeSolid
		);

		/*Novice::DrawLine
		(
			static_cast<int>(position_.x), static_cast<int>(position_.y  ),
			static_cast<int>(position_.x), static_cast<int>(position_.y + rand() % 700) ,
			WHITE
		);*/
		

	}

	
	Novice::ScreenPrintf(0, 0, "%f", position_.y);

	//エミッター(描画範囲)の描画
	emitter_->Draw();
}