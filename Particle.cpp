#include "Particle.h"
#include"Novice.h"
//コンストラクタ
Particle::Particle()
{
	this->emitter_ = new Emitter;
	this->subEmitter_ = new Emitter;

	this->position_ = { 0.0f,0.0f };			//雨の位置
	this->velocity_ = { 0.0f,0.0f };			//速度
	this->acceleration_ = { 0.0f,kGravity_ };	//加速度
	this->size_ = { 10.0f,10.0f };				//大きさ
	this->isActive_ = false;					//生成されているか
	this->mass_ = { 10.0f,10.0f };						//質量
	this->airResistance_ = { 0,0 };				//空気抵抗
	this->airResistanceAcceleration_ = { 0, 0 };	//空気抵抗による加速度

	this->wind_ = { 10.0f,0.0f };	//風

	this->restitution_ = 0.9f;		//跳ね返り係数
	this->ground_ = { 0,700.0f };	//地面の位置

	this->isSplash_ = false;
	for (int i = 0; i < numParticles; i++)
	{
		this->splashPosition_[i] = { 0.0f,0.0f };
		this->splashVelocity_[i] = { 0.0f,0.0f };
		this->splashSize_[i] = { 1.0f,1.0f };
		this->splashAcceleration_[i] = { 0.0f,kGravity_ };
	}


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
	if (this->isActive_ == false)
	{
		//エミッターの位置からランダムに位置を決める
		Vector2 min;
		Vector2 max;

		min.x = emitter_->GetPosition().x;
		max.x = emitter_->GetSize().x;
		min.y = emitter_->GetPosition().x + emitter_->GetSize().x / 2;
		max.y = emitter_->GetPosition().y - emitter_->GetSize().y / 4;

		this->position_.x = min.x + static_cast<float>(rand()) / RAND_MAX * (max.x - min.x);
		this->position_.y = emitter_->GetPosition().y - static_cast<float>(rand()) / RAND_MAX * 700.0f; // 100.0fはランダムな範囲の大きさを調整する値


		//生成する
		this->isActive_ = true;

	}

	//生成されていたら
	if (this->isActive_ == true)
	{


		//空気抵抗による加速度
		airResistance_ =
		{
			(this->k_ * -this->velocity_.x),
			(this->k_ * -this->velocity_.y)
		};

		//空気抵抗による加速度
		airResistanceAcceleration_ =
		{
			-airResistance_.x / this->mass_.x,
			-airResistance_.y / this->mass_.y
		};

		this->acceleration_.y = kGravity_ + airResistanceAcceleration_.y;

		//風力の適用
		acceleration_.x += wind_.x / mass_.x;
		acceleration_.y += wind_.y / mass_.y;





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


		const float positonX = position_.x;
		const float positionY = position_.y;
	

		lineStart_.x = positonX;
		lineStart_.y = positionY;
		lineEnd_.x = position_.x;
		lineEnd_.y = position_.y - 200.0f - static_cast<float>(rand() % 700);

		lineStart_.y += wind_.y * (1.0f / 60.0f);
		lineEnd_.y += wind_.y * (1.0f / 60.0f);

	}

	//地面に当たったときの跳ね返り
	if (this->isActive_ == true && this->position_.y >= this->ground_.y)
	{
		this->position_.y = this->ground_.y - this->size_.y / 2 - 1.0f;

		this->subEmitter_->SetPosition(this->position_);
		this->subEmitter_->SetSize(this->size_);

		


		isActive_ = false;

		isSplash_ = true;

	}

	if (isSplash_ == true)
	{


		for (int i = 0; i < numParticles; i++)
		{

			// パーティクルの角度と距離を生成
			angle = 90.0f + static_cast<float>(rand()) / RAND_MAX * 90.0f;

			distance = static_cast<float>(rand()) / RAND_MAX * subEmitter_->GetSize().x / 2;

			this->splashPosition_[i].x = subEmitter_->GetPosition().x + distance * cosf(angle * (static_cast<float>(M_PI) / 180.0f));
			this->splashPosition_[i].y = subEmitter_->GetPosition().y - distance * sinf(angle * (static_cast<float>(M_PI) / 180.0f));


			//速度を一定時間ごとに一定距離進ませる
			this->splashVelocity_[i].x += this->splashAcceleration_[i].x;
			this->splashVelocity_[i].y += this->splashAcceleration_[i].y;

			//位置に速度を足す(進む)
			this->splashPosition_[i].x += this->splashVelocity_[i].x * (1.0f / 60.0f);
			this->splashPosition_[i].y += this->splashVelocity_[i].y * (1.0f / 60.0f);

			// 跳ね返る速度の計算
			this->splashVelocity_[i].y = -this->splashVelocity_[i].y * this->restitution_;
		
			bool allParticlesOutsideScreen = true;

			if (splashPosition_[i].y <= 720)
			{
				allParticlesOutsideScreen = false;
				break;
			}

			if (allParticlesOutsideScreen == false)
			{
				isSplash_ = false;
			}

		}

	}
}



//描画
void Particle::Draw()
{

	//雨の描画
	if (this->isActive_ == true)	//生成されていたら描画する
	{/*
		Novice::DrawEllipse
		(
			static_cast<int>(position_.x), static_cast<int>(position_.y),
			static_cast<int>(this->size_.x / 2), static_cast<int>(this->size_.y / 2),
			0.0f, WHITE, kFillModeSolid
		);*/

		Novice::DrawLine
		(
			static_cast<int>(lineStart_.x), static_cast<int>(lineStart_.y),
			static_cast<int>(lineEnd_.x), static_cast<int>(lineEnd_.y),
			WHITE
		);


	}

	//水しぶきの描画
	if (isSplash_ == true)
	{
		for (int i = 0; i < numParticles; i++)
		{

			Novice::DrawEllipse
			(
				static_cast<int>(splashPosition_[i].x), static_cast<int>(splashPosition_[i].y),
				static_cast<int>(splashSize_[i].x), static_cast<int>(splashSize_[i].y),
				0.0f, WHITE, kFillModeSolid
			);
		}
	}

	//地面
	Novice::DrawLine
	(
		static_cast<int>(this->ground_.x), static_cast<int>(this->ground_.y),
		static_cast<int>(this->ground_.x + 1280), static_cast<int>(this->ground_.y),
		BLUE
	);


	//エミッター(描画範囲)の描画
	emitter_->Draw();
}