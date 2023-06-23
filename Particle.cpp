﻿#include "Particle.h"
#include"Novice.h"
#define _USE_MATH_DEFINES  
#include <math.h>
#include"ImGuiManager.h"

//コンストラクタ
Particle::Particle()
{
	this->emitter_ = new Emitter;
	this->subEmitter_ = new Emitter;

	this->position_ = { 0.0f,0.0f };			//雨の位置
	this->velocity_ = { 0.0f,0.0f };			//速度
	this->acceleration_ = { 0.0f,kGravity_.y };	//加速度
	this->size_ = 10.0f;						//大きさ
	this->isActive_ = false;					//生成されているか
	this->mass_ = 0;							//質量
	this->airResistance_ = { 0,0 };				//空気抵抗
	this->airResistanceAcceleration_ = { 0, 0 };	//空気抵抗による加速度

	this->angle = 0;
	this->distance = 0;
	this->endAcc_ = { 0,0, };
	this->endvel_ = { 0,0, };
	this->gravityAcceleration_ = { 0,0, };
	this->lineEnd_ = { 0,0, };
	this->lineStart_ = { 0,0 };
	this->random = 0;
	this->terminalVelocity_ = { 0,0 };
	this->endPos_ = { 0.0f,0.0f };
	this->windAcceleration_ = { 0,0 };

	rainDensity_ = 1000.0f;	//雨粒の密度
	airDensity_ = 1.225f;	//空気の密度
	k_ = 0.5f * 100;		//空気抵抗係数
	kGravity_ = { 0.0f, 9.8f * 100 };		//重力加速度



	this->wind_ = { 0, 0 };
	this->windSpeed_ = { 0.2f,0.0f };



	this->restitution_ = 0.9f;		//跳ね返り係数
	this->ground_ = { 0,700.0f };	//地面の位置

	this->isSplash_ = false;
	for (int i = 0; i < numParticles; i++)
	{
		this->splashPosition_[i] = { 0.0f,0.0f };
		this->splashVelocity_[i] = { 0.0f,0.0f };
		this->splashSize_[i] = { 1.0f,1.0f };
		this->splashAcceleration_[i] = { 0.0f,kGravity_.y };
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

	if (Novice::CheckHitKey(DIK_LEFT))
	{
		windSpeed_.x -= 0.001f;
	}
	if (Novice::CheckHitKey(DIK_RIGHT))
	{
		windSpeed_.x += 0.001f;
	}


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
		this->position_.y = emitter_->GetPosition().y - static_cast<float>(rand()) / RAND_MAX * 500.0f; // 100.0fはランダムな範囲の大きさを調整する値

		endPos_.x = position_.x;
		endPos_.y = position_.y;

		//生成する
		this->isActive_ = true;

	}

	//生成されていたら
	if (this->isActive_ == true)
	{

		//風力を求める
		wind_.x = 0.5f * airDensity_ * static_cast<float>(pow((windSpeed_.x), 2.0f)) * k_ * static_cast<float>(M_PI) * static_cast<float>(pow((size_ / 2.0f), 2.0f));
		wind_.y = 0.5f * airDensity_ * static_cast<float>(pow((windSpeed_.y), 2.0f)) * k_ * static_cast<float>(M_PI) * static_cast<float>(pow((size_ / 2.0f), 2.0f));
	
		//質量の計算
		mass_ = (4.0f / 3.0f) * static_cast<float>(M_PI) * static_cast<float>(pow((size_ / 2.0f), 3.0f)) * rainDensity_;
		
		//終端速度を求める
		terminalVelocity_.x = ((2 * rainDensity_ * kGravity_.x) / (airDensity_ * static_cast<float>(M_PI) * static_cast<float>(pow((size_ / 2.0f), 2.0f)) * k_));
		terminalVelocity_.y = ((2 * rainDensity_ * kGravity_.y) / (airDensity_ * static_cast<float>(M_PI) * static_cast<float>(pow((size_ / 2.0f), 2.0f)) * k_));

		terminalWindVelocity_ = terminalVelocity_;
		

		acceleration_.x = wind_.x / mass_;
		acceleration_.y = wind_.y / mass_;



		//速度の更新
		this->velocity_.x += (acceleration_.x + terminalWindVelocity_.x) * (1.0f / 60.0f);
		this->velocity_.y += (acceleration_.y + terminalWindVelocity_.y) * (1.0f / 60.0f);

	


		this->endvel_.x += terminalVelocity_.x * (1.0f / 60.0f);
		this->endvel_.y += terminalVelocity_.y * (1.0f / 60.0f);

		Vector2 copyEndVel;
		copyEndVel.x = position_.x;
		copyEndVel.y = position_.y;

	

		//位置の更新
		position_.x += this->velocity_.x * (1.0f / 60.0f) ;
		position_.y += this->velocity_.y * (1.0f / 60.0f) ;

		endPos_.x += this->endvel_.x * (1.0f / 60.0f) ;
		endPos_.y += this->endvel_.y * (1.0f / 60.0f) ;

		if (position_.y >= ground_.y)
		{
			isActive_ = false;
			this->velocity_ = { 0.0f,0.0f };
			this->endvel_ = { 0.0f,0.0f };
		}

	

		lineStart_.x = position_.x + wind_.x;
		lineStart_.y = position_.y + wind_.y;
		lineEnd_.x = endPos_.x;
		lineEnd_.y = endPos_.y-200 ;
	


	}

	//地面に当たったときの跳ね返り
	if (this->isActive_ == true && this->position_.y >= this->ground_.y)
	{
		this->position_.y = this->ground_.y - this->size_ / 2 - 1.0f;

		this->subEmitter_->SetPosition(this->position_);
		this->subEmitter_->SetSize(this->ground_);

		


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
	{
		/*Novice::DrawEllipse
		(
			static_cast<int>(position_.x), static_cast<int>(position_.y),
			static_cast<int>(this->size_ / 2), static_cast<int>(this->size_ / 2),
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



